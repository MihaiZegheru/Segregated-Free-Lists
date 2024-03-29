#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <command.h>
#include <sf_lists.h>
#include <stats_data_object.h>

typedef struct {

    s_sf_lists_t *sfl_src;
    s_sf_lists_t *sfl_dest;
	s_doubly_linked_list_t *dll_dest;
	s_doubly_linked_list_t *dll_dest_by_size;
	s_stats_data_object_t m_stats;
} s_workspace_t;

void app_init_sf_list(s_workspace_t *wks, s_command_IH_t *cmd) {
    wks->sfl_src = sf_lists_create(cmd->m_list_count, cmd->m_list_size,
            cmd->m_heap_start_addr, cmd->m_should_reconstitute);
    wks->sfl_dest = sf_lists_create(cmd->m_list_count, cmd->m_list_size,
            cmd->m_heap_start_addr, 0);

	wks->dll_dest = dll_create(0);
	wks->m_stats.m_total_mem = cmd->m_list_count * cmd->m_list_size;
	wks->m_stats.m_total_alloc_mem = 0;
	wks->m_stats.m_num_free_blocks = 0;
	wks->m_stats.m_num_alloc_blocks = 0;
	wks->m_stats.m_num_malloc_calls = 0;
	wks->m_stats.m_num_frag = 0;
	wks->m_stats.m_num_free_calls = 0;

	printf("%lu\n", cmd->m_heap_start_addr);
	size_t tag = 1;
    size_t virtual_addr = cmd->m_heap_start_addr;
    for (size_t i = 0; i < cmd->m_list_count; i++) {
		size_t node_size = (1 << 3) << i;
        size_t count = cmd->m_list_size / node_size;

		wks->m_stats.m_num_free_blocks += count;

        for (size_t j = 0; j < count; j++) {
            s_node_t *new_node = node_create(node_size, virtual_addr, tag,
					node_size, NULL);
            sf_lists_insert(wks->sfl_src, node_size, new_node);
            printf("%lu ", virtual_addr);
            virtual_addr += node_size;
			tag++;
        }
		printf("\n");
    }
}

// MALOC MOARE CAND DAU 1 CA ARG LA JOINGING LA NODES
void app_malloc_node(s_workspace_t *wks, s_command_M_t *cmd) {
    s_node_t *node;
	size_t node_size;

	// change die in err
    DIE(sf_lists_top(wks->sfl_src, &node, &node_size, cmd->m_size) == ET_EMPTY, "Didnt find");
	printf("%lu\n", node_size);
	printf("ADDR: %lu\n", node->m_virtual_addr);
	if (node_size != cmd->m_size) {
		// Split the node
		size_t new_addr = node->m_virtual_addr + cmd->m_size;
		size_t new_size = node_size - cmd->m_size;

		// Update node size
		node->m_size = cmd->m_size;

		// Keep the same node tag for rejoining and add new size
		s_node_t *new_node = node_create(0, new_addr, node->m_tag, new_size, NULL);
		new_node->m_data = (char *) node->m_data + cmd->m_size;

		// Insert allocated node
		// sf_lists_insert(wks->sfl_dest, cmd->m_size, node);
		dll_insert_by_addr(wks->dll_dest, node);
		dll_insert_by_size(wks->dll_dest_by_size, node);
		// Insert remainder node
		sf_lists_insert(wks->sfl_src, new_size, new_node);

		wks->m_stats.m_num_frag++;
	}
	else {
		// Insert the whole node
		// sf_lists_insert(wks->sfl_dest, node_size, node);
		dll_insert_by_addr(wks->dll_dest, node);
		wks->m_stats.m_num_free_blocks -= 1;
	}

	wks->m_stats.m_total_alloc_mem += cmd->m_size;
	wks->m_stats.m_num_alloc_blocks++;
	wks->m_stats.m_num_malloc_calls++;
}

void app_free_node(s_workspace_t *wks, s_command_F_t *cmd) {
	s_node_t *node;
	// size_t node_size;

	// change die in err
    // DIE(sf_list_remove_by_addr(wks->sfl_dest, &node, &node_size, cmd->m_addr) == ET_INVALID_FREE,
	// 		"Didnt find");
	node = dll_remove_by_addr(wks->dll_dest, cmd->m_addr);
	if (node == NULL) {
		printf("cant");
		return;
	}
	dll_remove_by_addr(wks->dll_dest_by_size, cmd->m_addr);

	printf("%lu\n", node->m_virtual_addr);
	wks->m_stats.m_total_alloc_mem -= node->m_size;
	wks->m_stats.m_num_alloc_blocks--;
	wks->m_stats.m_num_free_calls++;
	// sf_lists_insert(wks->sfl_src, node_size, node);

	uint8_t joined = sf_lists_insert(wks->sfl_src, node->m_size, node);
	if (joined) {
		wks->m_stats.m_num_frag--;
	}
	else {
		wks->m_stats.m_num_free_blocks++;
	}
}

void app_read(s_workspace_t *wks, s_command_R_t *cmd) {
	if (dll_is_empty(wks->dll_dest)) {
		printf("mem doesnt ex");
		return;
	}

	s_doubly_linked_list_t *dll = wks->dll_dest;
	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size - 1 && cmd->m_src - curr_node->m_virtual_addr >= curr_node->m_size) {
		curr_node = curr_node->m_next;
		idx++;
	}

	if (cmd->m_src - curr_node->m_virtual_addr >= curr_node->m_size) {
		printf("seg fault 1");
		return;
	}

	printf("INFO: %lu %lu %lu\n", curr_node->m_virtual_addr, curr_node->m_size, cmd->m_src);

	// coudl have errors here due to unsigned to signed conversion
	s_node_t *starting_node = curr_node;
	int64_t left_size = (int64_t)cmd->m_size - (curr_node->m_size - (cmd->m_src - curr_node->m_virtual_addr));
	printf("LEFT SIZE: %lu\n", left_size);

	while (idx < dll->m_size - 1 && left_size > 0) {
		if (curr_node->m_virtual_addr + curr_node->m_size != curr_node->m_next->m_virtual_addr) {
			break;
		}
		curr_node = curr_node->m_next;
		left_size -= curr_node->m_size;
		idx++;
		printf("LEFT SIZE: %lu\n", left_size);
	}

	if (left_size > 0) {
		// err cuz invalid address
		printf("seg fault 2");
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
	printf("JJJ");
	while (left_size > 0) {
		for (size_t j = 0; j < curr_node->m_size && left_size > 0; j++) {
			printf("%c", *((char *)curr_node->m_data + j));
			left_size--;
		}
		curr_node = curr_node->m_next;
	}
	printf("\n");
}

void app_write(s_workspace_t *wks, s_command_W_t *cmd) {
	if (dll_is_empty(wks->dll_dest)) {
		printf("mem doesnt ex");
		return;
	}

	s_doubly_linked_list_t *dll = wks->dll_dest;
	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size - 1 && cmd->m_dest - curr_node->m_virtual_addr >= curr_node->m_size) {
		curr_node = curr_node->m_next;
		idx++;
	}

	if (cmd->m_dest - curr_node->m_virtual_addr >= curr_node->m_size) {
		printf("seg fault 1");
		return;
	}

	printf("INFO: %lu %lu %lu\n", curr_node->m_virtual_addr, curr_node->m_size, cmd->m_dest);

	// coudl have errors here due to unsigned to signed conversion
	s_node_t *starting_node = curr_node;
	int64_t left_size = (int64_t)cmd->m_size - (curr_node->m_size - (cmd->m_dest - curr_node->m_virtual_addr));
	printf("LEFT SIZE: %lu\n", left_size);

	while (idx < dll->m_size - 1 && left_size > 0) {
		if (curr_node->m_virtual_addr + curr_node->m_size != curr_node->m_next->m_virtual_addr) {
			break;
		}
		curr_node = curr_node->m_next;
		left_size -= curr_node->m_size;
		idx++;
		printf("LEFT SIZE: %lu\n", left_size);
	}

	if (left_size > 0) {
		// err cuz invalid address
		printf("seg fault 2");
		return;
	}

	curr_node = starting_node;
	idx = 0;
	printf("%s\n", cmd->m_src);
	printf("%s\n", cmd->m_src);
	size_t offset = cmd->m_dest - curr_node->m_virtual_addr;
	printf("%ld\n", offset);
	printf("%s\n", cmd->m_src);
	for (size_t j = offset; idx < cmd->m_size && j < curr_node->m_size &&
			!string_utils_is_end_char(cmd->m_src[idx]); j++) {
		printf("%s\n", cmd->m_src);
		*((char *)curr_node->m_data + j) = cmd->m_src[idx];
		printf("%c %c %lu\n", *((char *)curr_node->m_data + j), cmd->m_src[idx], idx);
		printf("%s\n", cmd->m_src);
		idx++;
	}

	curr_node = curr_node->m_next;
	while (idx < cmd->m_size && !string_utils_is_end_char(cmd->m_src[idx])) {
		for (size_t j = 0; j < curr_node->m_size && !string_utils_is_end_char(cmd->m_src[idx]); j++) {
			*((char *)curr_node->m_data + j) = cmd->m_src[idx];
			idx++;
		}
		curr_node = curr_node->m_next;
	}
	printf("\n");
}

void app_dump_memory(s_workspace_t *wks, s_command_W_t *cmd) {
	printf("+++++DUMP+++++\n");

	printf("Total memory: %lld bytes", wks->m_stats.m_total_mem);
	printf("Total allocated memory: %lld bytes", wks->m_stats.m_total_alloc_mem);
	printf("Total free memory: %lld bytes", wks->m_stats.m_total_mem -
			wks->m_stats.m_total_alloc_mem);
	printf("Free blocks: %lld", wks->m_stats.m_num_free_blocks);
	printf("Number of allocated blocks: %lld ", wks->m_stats.m_num_alloc_blocks);
	printf("Number of malloc calls: %lld ", wks->m_stats.m_num_malloc_calls);
	printf("Number of fragmentations: %lld ", wks->m_stats.m_num_frag);
	printf("Number of free calls: %lld ", wks->m_stats.m_num_free_calls);

	for (size_t i = 0; i < wks->sfl_src->m_size; i++) {
		if (wks->sfl_src->m_dll_array[i]->m_size == 0) {
			continue;
		}

		s_doubly_linked_list_t *dll = wks->sfl_src->m_dll_array[i];
		size_t count = dll->m_size;

		printf("Blocks with %lld bytes - %lld free block(s) :", i, count);

		s_node_t *curr_node = dll->m_head;
		for (size_t j = 0; j < count; j++) {
			printf(" %lld", curr_node->m_virtual_addr); // add conv to hexa----------------------------------------------
			curr_node = (s_node_t *) curr_node->m_next;
		}
		printf("\n");
	}

	printf("Allocated blocks :");
	s_node_t *curr_node = wks->dll_dest_by_size->m_head;
	for (size_t i = 0; i < wks->dll_dest_by_size->m_size; i++) {
		printf(" (%lld - %lld)", curr_node->m_virtual_addr, curr_node->m_size);
		curr_node = (s_node_t *) curr_node->m_next;
	}
	printf("\n");

	printf("-----DUMP-----\n");
}

void app_tick() {
    s_workspace_t wks;
	u_command_t cmd;


	while (1) {
		command_read(&cmd);

		switch(cmd.m_default_cmd.command_type) {
		case CT_NONE:
			break;
		case CT_INIT_HEAP:
			app_init_sf_list(&wks, &(cmd.m_IH_cmd));
			break;
		case CT_MALLOC:
			app_malloc_node(&wks, &(cmd.m_M_cmd));
			break;
		case CT_FREE:
			app_free_node(&wks, &(cmd.m_F_cmd));
			break;
		case CT_READ:
			app_read(&wks, &(cmd.m_R_cmd));
			break;
		case CT_WRITE:
			app_write(&wks, &(cmd.m_W_cmd));
			break;
		case CT_DUMP_MEMORY:
			break;
		case CT_DESTROY_HEAP:
			break;
		}

		printf("\n");
	}

}

#endif // APP_MANAGER_H__
