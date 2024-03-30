#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <command.h>
#include <sf_lists.h>
#include <stats_data_object.h>
#include <string_utils.h>

typedef struct {
    s_sf_lists_t *sfl_src;
	s_doubly_linked_list_t *dll_dest;
	s_stats_data_object_t m_stats;
} s_workspace_t;

void app_init_sf_list(s_workspace_t *wks, s_command_IH_t *cmd);
void app_malloc_node(s_workspace_t *wks, s_command_M_t *cmd);
void app_free_node(s_workspace_t *wks, s_command_F_t *cmd);
void app_read(s_workspace_t *wks, s_command_R_t *cmd);
void app_write(s_workspace_t *wks, s_command_W_t *cmd);
void app_dump_memory(s_workspace_t *wks);
void app_destroy_heap(s_workspace_t *wks);

uint8_t app_tick(s_workspace_t *wks, u_command_t *cmd,
		char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE]);
void app_main_loop();

#endif // APP_MANAGER_H__
