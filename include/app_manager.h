#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <command.h>
#include <sf_lists.h>

typedef struct {
    s_sf_lists_t *sfl_src;
    s_sf_lists_t *sfl_dest;
} s_workspace_t;

void app_init_sf_list(s_workspace_t *wks, s_command_IH_t *cmd) {
    wks->sfl_src = sf_lists_create(cmd->m_list_count, cmd->m_list_size,
            cmd->m_heap_start_addr, cmd->m_should_reconstitute);
    wks->sfl_dest = sf_lists_create(cmd->m_list_count, cmd->m_list_size,
            cmd->m_heap_start_addr, cmd->m_should_reconstitute);

	size_t tag = 0;
    size_t virtual_addr = cmd->m_heap_start_addr;
    for (size_t i = 0; i < cmd->m_list_count; i++) {
		size_t node_size = (1 << 3) << i;
        size_t count = cmd->m_list_size / node_size;

        for (size_t j = 0; j < count; j++) {
            s_node_t *new_node = node_create(node_size, virtual_addr, tag, NULL);
            sf_lists_insert(wks->sfl_src, node_size, new_node);
            printf("%llu ", virtual_addr);
            virtual_addr += node_size;
			tag++;
        }
    }
}

void app_malloc_node(s_workspace_t *wks, s_command_M_t *cmd) {
    s_node_t *node;
	size_t node_size;

	// change die in err
    DIE(sf_lists_top(wks->sfl_src, &node, &node_size, cmd->m_size) == ET_EMPTY, "Didnt find");
	printf("%lld\n", node_size);
	if (node_size != cmd->m_size) {
		// split
		size_t new_addr = node->m_virtual_addr + cmd->m_size;
		size_t new_size = node_size - cmd->m_size;

		s_node_t *new_node = node_create(0, new_addr, node->m_tag, NULL);
		new_node->m_data = (char *) node->m_data + cmd->m_size;

		sf_lists_insert(wks->sfl_src, new_size, new_node);
	}
	else {
		sf_lists_insert(wks->sfl_dest, node_size, node);
	}
}

void app_tick() {
    s_workspace_t wks;
	u_command_t cmd;

	while (1) {
		command_read(&cmd);

		switch(cmd.m_default_cmd.command_type) {
		case CT_INIT_HEAP:
			app_init_sf_list(&wks, &(cmd.m_IH_cmd));
			break;
		case CT_MALLOC:
			app_malloc_node(&wks, &(cmd.m_M_cmd));
			break;
		}

		printf("\n");
	}

}

#endif // APP_MANAGER_H__