#include <app_manager.h>

void app_init_sf_list(s_workspace_t *wks, s_command_IH_t *cmd)
{
	wks->sfl_src = sf_lists_create(cmd->m_list_count, cmd->m_list_size,
								   cmd->m_heap_start_addr,
								   cmd->m_should_reconstitute);

	wks->dll_dest = dll_create(0);

	wks->m_stats.m_total_mem = cmd->m_list_count * cmd->m_list_size;
	wks->m_stats.m_total_alloc_mem = 0;
	wks->m_stats.m_num_free_blocks = 0;
	wks->m_stats.m_num_alloc_blocks = 0;
	wks->m_stats.m_num_malloc_calls = 0;
	wks->m_stats.m_num_frag = 0;
	wks->m_stats.m_num_free_calls = 0;

	size_t tag = 1;
	size_t virtual_addr = cmd->m_heap_start_addr;
	for (size_t i = 0; i < cmd->m_list_count; i++) {
		size_t node_size = (1 << 3) << i;
		size_t count = cmd->m_list_size / node_size;

		wks->m_stats.m_num_free_blocks += count;

		for (size_t j = 0; j < count; j++) {
			s_node_t *new_node = node_create(node_size, virtual_addr, tag,
					node_size, NULL, 0);
			sf_lists_insert(wks->sfl_src, node_size, new_node);

			virtual_addr += node_size;
			tag++;
		}
	}
}

void app_malloc_node(s_workspace_t *wks, s_command_M_t *cmd)
{
	s_node_t *node;
	size_t node_size;

	if (sf_lists_top(wks->sfl_src, &node, &node_size, cmd->m_size) ==
					 ET_EMPTY) {
		printf(FAILED_TO_ALLOCATE);
		return;
	}

	if (node_size != cmd->m_size) {
		// Split the node
		size_t new_addr = node->m_virtual_addr + cmd->m_size;
		size_t new_size = node_size - cmd->m_size;

		// Update node size
		node->m_size = cmd->m_size;

		// Keep the same node tag for rejoining and add new size
		s_node_t *new_node = node_create(0, new_addr, node->m_tag, new_size,
										 NULL, 1);
		new_node->m_data = (char *)node->m_data + cmd->m_size;

		// Insert allocated node
		node->m_prev = NULL;
		node->m_next = NULL;
		dll_insert_by_addr(wks->dll_dest, node);

		// Insert remaining node
		sf_lists_insert(wks->sfl_src, new_size, new_node);

		wks->m_stats.m_num_frag++;
	} else {
		// Insert the whole node
		node->m_prev = NULL;
		node->m_next = NULL;
		dll_insert_by_addr(wks->dll_dest, node);

		wks->m_stats.m_num_free_blocks -= 1;
	}

	wks->m_stats.m_total_alloc_mem += cmd->m_size;
	wks->m_stats.m_num_alloc_blocks++;
	wks->m_stats.m_num_malloc_calls++;
}

void app_free_node(s_workspace_t *wks, s_command_F_t *cmd)
{
	s_node_t *node;

	node = dll_remove_by_addr(wks->dll_dest, cmd->m_addr);
	if (!node) {
		printf(INVALID_FREE);
		return;
	}

	wks->m_stats.m_total_alloc_mem -= node->m_size;
	wks->m_stats.m_num_alloc_blocks--;
	wks->m_stats.m_num_free_calls++;

	__u8 joined = sf_lists_insert(wks->sfl_src, node->m_size, node);
	if (joined)
		wks->m_stats.m_num_free_blocks -= joined - 1;
	else
		wks->m_stats.m_num_free_blocks++;
}

void app_read(s_workspace_t *wks, s_command_R_t *cmd)
{
	if (dll_is_empty(wks->dll_dest)) {
		printf(INVALID_READ);
		exit(0);
	}

	s_doubly_linked_list_t *dll = wks->dll_dest;
	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size - 1 &&
		   cmd->m_src - curr_node->m_virtual_addr >= curr_node->m_size) {
		curr_node = curr_node->m_next;
		idx++;
	}

	if (cmd->m_src - curr_node->m_virtual_addr >= curr_node->m_size) {
		printf(SEG_FAULT);
		app_dump_memory(wks);
		app_destroy_heap(wks);
		exit(0);
	}

	s_node_t *starting_node = curr_node;
	__s64 left_size = (__s64)cmd->m_size -
						(curr_node->m_size -
						(cmd->m_src - curr_node->m_virtual_addr));

	while (idx < dll->m_size - 1 && left_size > 0) {
		if (curr_node->m_virtual_addr + curr_node->m_size !=
			curr_node->m_next->m_virtual_addr) {
			break;
		}
		curr_node = curr_node->m_next;
		left_size -= curr_node->m_size;
		idx++;
	}

	if (left_size > 0) {
		printf(SEG_FAULT);
		app_dump_memory(wks);
		app_destroy_heap(wks);
		exit(0);
		return;
	}

	curr_node = starting_node;
	left_size = cmd->m_size;
	size_t offset = cmd->m_src - curr_node->m_virtual_addr;
	for (size_t j = offset; left_size > 0 && j < curr_node->m_size &&
		 left_size > 0; j++) {
		printf("%c", *((char *)curr_node->m_data + j));
		left_size--;
	}

	curr_node = curr_node->m_next;
	while (left_size > 0) {
		for (size_t j = 0; j < curr_node->m_size && left_size > 0; j++) {
			printf("%c", *((char *)curr_node->m_data + j));
			left_size--;
		}
		curr_node = curr_node->m_next;
	}
	printf("\n");
}

void app_write(s_workspace_t *wks, s_command_W_t *cmd)
{
	if (dll_is_empty(wks->dll_dest)) {
		printf(INVALID_READ);
		return;
	}

	s_doubly_linked_list_t *dll = wks->dll_dest;
	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	size_t actual_size = strlen(cmd->m_src);
	if (actual_size < cmd->m_size)
		cmd->m_size = actual_size;

	while (idx < dll->m_size - 1 && cmd->m_dest - curr_node->m_virtual_addr >=
		   curr_node->m_size) {
		curr_node = curr_node->m_next;
		idx++;
	}

	if (cmd->m_dest - curr_node->m_virtual_addr >= curr_node->m_size) {
		printf(SEG_FAULT);
		app_dump_memory(wks);
		app_destroy_heap(wks);
		exit(0);
		return;
	}

	s_node_t *starting_node = curr_node;
	__s64 left_size = (__s64)cmd->m_size -
					  (curr_node->m_size -
					  (cmd->m_dest - curr_node->m_virtual_addr));

	while (idx < dll->m_size - 1 && left_size > 0) {
		if (curr_node->m_virtual_addr + curr_node->m_size !=
			curr_node->m_next->m_virtual_addr) {
			break;
		}

		curr_node = curr_node->m_next;
		left_size -= curr_node->m_size;
		idx++;
	}

	if (left_size > 0) {
		printf(SEG_FAULT);
		app_dump_memory(wks);
		app_destroy_heap(wks);
		exit(0);
		return;
	}

	curr_node = starting_node;
	idx = 0;
	size_t offset = cmd->m_dest - curr_node->m_virtual_addr;

	for (size_t j = offset; idx < cmd->m_size && j < curr_node->m_size &&
		 !string_utils_is_end_char(cmd->m_src[idx]); j++) {
		if (cmd->m_src[idx] == '\"')
			continue;

		*((char *)curr_node->m_data + j) = cmd->m_src[idx];
		idx++;
	}

	curr_node = curr_node->m_next;
	while (idx < cmd->m_size && !string_utils_is_end_char(cmd->m_src[idx])) {
		for (size_t j = 0; j < curr_node->m_size &&
			 !string_utils_is_end_char(cmd->m_src[idx]); j++) {
			if (cmd->m_src[idx] == '\"')
				continue;

			*((char *)curr_node->m_data + j) = cmd->m_src[idx];
			idx++;
		}
		curr_node = curr_node->m_next;
	}
}

void app_dump_memory(s_workspace_t *wks)
{
	printf("+++++DUMP+++++\n");
	printf("Total memory: %ld bytes\n", wks->m_stats.m_total_mem);
	printf("Total allocated memory: %ld bytes\n",
		   wks->m_stats.m_total_alloc_mem);
	printf("Total free memory: %ld bytes\n", wks->m_stats.m_total_mem -
		   wks->m_stats.m_total_alloc_mem);
	printf("Free blocks: %ld\n", wks->m_stats.m_num_free_blocks);
	printf("Number of allocated blocks: %ld\n",
		   wks->m_stats.m_num_alloc_blocks);
	printf("Number of malloc calls: %ld\n", wks->m_stats.m_num_malloc_calls);
	printf("Number of fragmentations: %ld\n", wks->m_stats.m_num_frag);
	printf("Number of free calls: %ld\n", wks->m_stats.m_num_free_calls);

	for (size_t i = 0; i < wks->sfl_src->m_size; i++) {
		if (wks->sfl_src->m_dll_array[i]->m_size == 0)
			continue;

		s_doubly_linked_list_t *dll = wks->sfl_src->m_dll_array[i];
		size_t count = dll->m_size;

		printf("Blocks with %ld bytes - %ld free block(s) :", i, count);

		s_node_t *curr_node = dll->m_head;
		for (size_t j = 0; j < count; j++) {
			printf(" 0x%lx", curr_node->m_virtual_addr);
			curr_node = (s_node_t *)curr_node->m_next;
		}
		printf("\n");
	}

	printf("Allocated blocks :");
	if (dll_is_empty(wks->dll_dest)) {
		printf("\n");
		printf("-----DUMP-----\n");
		return;
	}

	s_node_t *curr_node = wks->dll_dest->m_head;
	printf(" (0x%lx - %ld)", curr_node->m_virtual_addr, curr_node->m_size);

	for (size_t i = 1; i < wks->dll_dest->m_size; i++) {
		curr_node = (s_node_t *)curr_node->m_next;
		printf(" (0x%lx - %ld)", curr_node->m_virtual_addr, curr_node->m_size);
	}
	printf("\n");

	printf("-----DUMP-----\n");
}

void app_destroy_heap(s_workspace_t *wks)
{
	dll_destroy(wks->dll_dest);
	sf_lists_destroy(wks->sfl_src);
}

static void e_app_init_input_buffer
		(char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE])
{
	for (size_t i = 0; i < MAX_COMMAND_PARAMS; i++)
		for (size_t j = 0; j < MAX_LINE_SIZE; j++)
			buffer[i][j] = '\0';
}

uint8_t app_tick(s_workspace_t *wks, u_command_t *cmd,
				 char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE])
{
		command_read(cmd, buffer);

		switch (cmd->m_default_cmd.command_type) {
		case CT_NONE:
			break;
		case CT_INIT_HEAP:
			app_init_sf_list(wks, &cmd->m_IH_cmd);
			break;
		case CT_MALLOC:
			app_malloc_node(wks, &cmd->m_M_cmd);
			break;
		case CT_FREE:
			app_free_node(wks, &cmd->m_F_cmd);
			break;
		case CT_READ:
			app_read(wks, &cmd->m_R_cmd);
			break;
		case CT_WRITE:
			app_write(wks, &cmd->m_W_cmd);
			break;
		case CT_DUMP_MEMORY:
			app_dump_memory(wks);
			break;
		case CT_DESTROY_HEAP:
			app_destroy_heap(wks);
			return 0;
		}

	return 1;
}

void app_main_loop(void)
{
	s_workspace_t wks;
	u_command_t cmd;

	char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE];
	e_app_init_input_buffer(buffer);

	__u8 is_running = app_tick(&wks, &cmd, buffer);
	while (is_running)
		is_running = app_tick(&wks, &cmd, buffer);
}
