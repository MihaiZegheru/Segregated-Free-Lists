#ifndef NODE_H__
#define NODE_H__

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node_t {
	void *m_data;
	size_t m_virtual_addr;
	size_t m_tag;
	size_t m_size;
	struct s_node_t *m_prev;
	struct s_node_t *m_next;
} s_node_t;

s_node_t *node_create(size_t data_size, size_t virtual_addr, size_t tag, size_t size, void *data);
void node_destory(s_node_t *node);
void node_light_destory(s_node_t *node);

#endif // NODE_H__
