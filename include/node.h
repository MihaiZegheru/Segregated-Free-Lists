#ifndef NODE_H__
#define NODE_H__

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <linux/types.h>

#include <macro_definitions.h>

/**
 * @brief Node for a doubly linked list.
 *
 */
typedef struct s_node_t {
	/**
	 * @brief Data stored.
	 *
	 */
	void *m_data;
	/**
	 * @brief Virtual address.
	 *
	 */
	size_t m_virtual_addr;
	/**
	 * @brief Tag.
	 * @note Used for reconstructing nodes.
	 *
	 */
	size_t m_tag;
	/**
	 * @brief The size of the data stored.
	 *
	 */
	size_t m_size;
	/**
	 * @brief Wether the node is a fragment.
	 *
	 */
	__u8 m_is_fragment;
	/**
	 * @brief Pointer to previous node.
	 *
	 */
	struct s_node_t *m_prev;
		/**
	 * @brief Pointer to next node.
	 *
	 */
	struct s_node_t *m_next;
} s_node_t;

/**
 * @brief Creates a new node.
 *
 * @param data_size
 * @param virtual_addr
 * @param tag
 * @param size
 * @param data
 * @param is_fragment
 * @return s_node_t*
 */
s_node_t *node_create(size_t data_size, size_t virtual_addr, size_t tag,
					  size_t size, void *data, __u8 is_fragment);

/**
 * @brief Destyroys a node.
 *
 * @param node
 */
void node_destory(s_node_t *node);

#endif // NODE_H__
