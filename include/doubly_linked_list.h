/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef DOUBLY_LINKED_LIST_H__
#define DOUBLY_LINKED_LIST_H__

#include <stdlib.h>
#include <inttypes.h>
#include <linux/types.h>

#include <node.h>
#include <macro_definitions.h>

/**
 * @brief Doubly linked list.
 *
 */
typedef struct {
	/**
	 * @brief The first node.
	 *
	 */
	s_node_t *m_head;
	/**
	 * @brief Size of the data stored in the nodes.
	 *
	 */
	size_t m_data_size;
	/**
	 * @brief Size of the list.
	 *
	 */
	size_t m_size;
} s_doubly_linked_list_t;

/**
 * @brief Creates a new DLL.
 *
 * @param data_size
 * @return s_doubly_linked_list_t*
 */
s_doubly_linked_list_t *dll_create(size_t data_size);

/**
 * @brief Destroys a DLL.
 *
 * @param dll
 */
void dll_destroy(s_doubly_linked_list_t *dll);

/**
 * @brief Returns true if the DLL is empty.
 *
 * @param dll
 * @return int8_t
 */
int8_t dll_is_empty(s_doubly_linked_list_t *dll);

/**
 * @brief Get the node at the position.
 *
 * @param dll
 * @param pos
 * @return s_node_t*
 */
s_node_t *dll_get_node(s_doubly_linked_list_t *dll, size_t pos);

/**
 * @brief Pushes a node at the head.
 *
 * @param dll
 * @param node
 */
void dll_insert_first(s_doubly_linked_list_t *dll, s_node_t *node);

/**
 * @brief Pushes a node at the tail.
 *
 * @param dll
 * @param node
 */
void dll_insert_last(s_doubly_linked_list_t *dll, s_node_t *node);

/**
 * @brief Pushes a node at the given index.
 *
 * @param dll
 * @param pos
 * @param node
 */
void dll_insert(s_doubly_linked_list_t *dll, size_t pos, s_node_t *node);

/**
 * @brief Pushes a node before the next higher address.
 *
 * @param dll
 * @param node
 */
void dll_insert_by_addr(s_doubly_linked_list_t *dll, s_node_t *node);

/**
 * @brief Pushes a node before the next higher size.
 *
 * @param dll
 * @param node
 */
void dll_insert_by_size(s_doubly_linked_list_t *dll, s_node_t *node);

/**
 * @brief Removes the node from the head.
 *
 * @param dll
 * @return s_node_t*
 */
s_node_t *dll_remove_first(s_doubly_linked_list_t *dll);

/**
 * @brief Removes the node from the tail.
 *
 * @param dll
 * @return s_node_t*
 */
s_node_t *dll_remove_last(s_doubly_linked_list_t *dll);

/**
 * @brief Removes the node at the given index.
 *
 * @param dll
 * @param pos
 * @return s_node_t*
 */
s_node_t *dll_remove(s_doubly_linked_list_t *dll, size_t pos);

/**
 * @brief Removes the node with the address. If not found, returns NULL.
 *
 * @param dll
 * @param node
 */
s_node_t *dll_remove_by_addr(s_doubly_linked_list_t *dll, size_t addr);

/**
 * @brief Removes the node from the contiguously allocated address, prior to the
 * provided one. If not found, returns NULL.
 *
 * @param dll
 * @param tag
 * @param curr_addr
 * @return s_node_t*
 */
s_node_t *dll_remove_prev(s_doubly_linked_list_t *dll, size_t tag,
						  size_t curr_addr);

/**
 * @brief Returns the node from the next contiguously allocated address
 * follwoing from the provided one. If not found, returns NULL.
 *
 * @param dll
 * @param tag
 * @param next_addr
 * @return s_node_t*
 */
s_node_t *dll_remove_next(s_doubly_linked_list_t *dll, size_t tag,
						  size_t next_addr);

#endif // DOUBLY_LINKED_LIST_H__
