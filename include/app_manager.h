#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <command.h>
#include <sf_lists.h>
#include <stats_data_object.h>
#include <string_utils.h>
#include <linux/types.h>

/**
 * @brief Stores the objects that the program is currently opperating on
 *
 */
typedef struct {
	/**
	 * @brief The heap containing the free nodes ordered by size, then by
	 * address
	 *
	 */
	s_sf_lists_t *sfl_src;
	/**
	 * @brief The list containing the allocated nodes ordered by address
	 *
	 */
	s_doubly_linked_list_t *dll_dest;
	/**
	 * @brief The statistics tracked for performing DUMP_MEMORY
	 *
	 */
	s_stats_data_object_t m_stats;
} s_workspace_t;

/**
 * @brief Main loop of the app
 *
 */
void app_main_loop(void);

#endif // APP_MANAGER_H__
