#ifndef NODE_H__
#define NODE_H__

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void *m_data;
	size_t virtual_addr;
	void *m_prev;
	void *m_next;
} s_node_t;

s_node_t *node_create(size_t data_size, void *data) {
	s_node_t *node = (s_node_t *) malloc(sizeof(s_node_t));

	node->m_data = malloc(data_size);
	memcpy(node->m_data, data, data_size);

	node->m_prev = NULL;
	node->m_next = NULL;
	node->virtual_addr = 0;

	return node;
}

void node_destory(s_node_t *node) {
	free(node->m_data);
	free(node);
}


#endif // NODE_H__