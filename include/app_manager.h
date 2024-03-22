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

    size_t virtual_addr = cmd->m_heap_start_addr;
    for (size_t i = 0; i < cmd->m_list_count; i++) {
        size_t count = cmd->m_list_size / (1 << i);
        for (size_t j = 0; j < count; j++) {
            s_node_t *new_node = node_create((1 << i) * sizeof(char), virtual_addr,
                    NULL);
            sf_lists_insert(wks->sfl_src, i, new_node);
            // printf("%llu ", virtual_addr);
            virtual_addr += (1 << i);
        }
    }
}

void app_malloc_node(s_workspace_t *wks, s_command_M_t *cmd) {
    s_node_t *node;

    s_doubly_linked_list_t *dll = wks->sfl_src->m_dll_array[cmd->m_size];
    assert(sf_lists_remove(dll, node, cmd->m_size) != NULL)
}

void app_tick() {
    s_workspace_t wks;
	u_command_t cmd;
	command_read(&cmd);
    app_init_sf_list(&wks, &(cmd.m_IH_cmd));
}

#endif // APP_MANAGER_H__