#include <node.h>

s_node_t *node_create(size_t data_size, size_t vitual_addr, void *data) {
	s_node_t *node = (s_node_t *) malloc(sizeof(s_node_t));

	node->m_data = malloc(data_size);
	if (data != NULL) {
		memcpy(node->m_data, data, data_size);
	}

	node->m_prev = NULL;
	node->m_next = NULL;
	node->m_virtual_addr = vitual_addr;

	return node;
}

void node_destory(s_node_t *node) {
	free(node->m_data);
	free(node);
}
