#include <node.h>

s_node_t *node_create(size_t data_size, size_t virtual_addr, size_t tag,
		size_t size, void *data) {

	s_node_t *node = (s_node_t *) malloc(sizeof(s_node_t));

	node->m_data = malloc(data_size);
	if (data != NULL) {
		memcpy(node->m_data, data, data_size);
	}

	node->m_prev = NULL;
	node->m_next = NULL;
	node->m_virtual_addr = virtual_addr;
	node->m_tag = tag;
	node->m_size = size;

	return node;
}

void node_destory(s_node_t *node) {
	free(node->m_data);
	free(node);
}
