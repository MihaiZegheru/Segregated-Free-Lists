/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef SF_LISTS_H__
#define SF_LISTS_H__

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <linux/types.h>

#include <doubly_linked_list.h>
#include <macro_definitions.h>
#include <error_type.h>

/**
 * @brief Segregated free lists.
 *
 */
typedef struct {
	/**
	 * @brief The stored doubly linked lists.
	 *
	 */
	s_doubly_linked_list_t **m_dll_array;
	/**
	 * @brief The size of the SFL.
	 *
	 */
	size_t m_size;
	/**
	 * @brief The size of the lists in bytes.
	 *
	 */
	size_t m_lists_size;
	/**
	 * @brief Starting virtual address of the SFL.
	 *
	 */
	size_t m_virtual_addr;
	/**
	 * @brief Wether or not nodes should reconstitute.
	 *
	 */
	__s8 m_should_reconstitute;
} s_sf_lists_t;

/**
 * @brief Creates a new SFL.
 *
 * @param size
 * @param lists_size
 * @param virtual_addr
 * @param should_reconstitute
 * @return s_sf_lists_t*
 * @note Simulates a HEAP
 */
s_sf_lists_t *sf_lists_create(size_t size, size_t lists_size,
							  size_t virtual_addr, __s8 should_reconstitute);

/**
 * @brief Destroys a SFL.
 *
 * @param sf_lists
 */
void sf_lists_destroy(s_sf_lists_t *sf_lists);

/**
 * @brief Pushes a node into the SFL.
 *
 * @param sf_lists
 * @param data_size
 * @param node
 * @return __u8
 */
__u8 sf_lists_insert(s_sf_lists_t *sf_lists, size_t data_size, s_node_t *node);

/**
 * @brief Get the smallest node at the first address to fit for the given size.
 * It will match to the equal or higher size nodes, prioritising the lowest
 * address.
 *
 * @param sf_list
 * @param out_node
 * @param out_node_size
 * @param data_size
 * @return e_error_type_t
 */
e_error_type_t sf_lists_top(s_sf_lists_t *sf_list, s_node_t **out_node,
							size_t *out_node_size, size_t data_size);

/**
 * @brief Remove a node from the SFL based on the provided virtual address.
 *
 * @param sf_lists
 * @param out_node
 * @param out_node_size
 * @param addr
 * @return e_error_type_t
 */
e_error_type_t sf_list_remove_by_addr(s_sf_lists_t *sf_lists,
									  s_node_t **out_node,
									  size_t *out_node_size, size_t addr);

/**
 * @brief Remove a node from the SFL based on the provided tag.
 *
 * @param sf_lists
 * @param out_node
 * @param out_node_size
 * @param tag
 * @return e_error_type_t
 * @note This is useful for reconstructing fragmented nodes.
 */
e_error_type_t sf_list_remove_by_tag(s_sf_lists_t *sf_lists,
									 s_node_t **out_node, size_t *out_node_size,
									 size_t tag);

#endif // SF_LISTS_H__
