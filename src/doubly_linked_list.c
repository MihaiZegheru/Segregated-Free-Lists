#include <doubly_linked_list.h>

s_doubly_linked_list_t *dll_create(size_t data_size) {
	s_doubly_linked_list_t *dll = malloc(sizeof(s_doubly_linked_list_t));
	// check if it did
	dll->m_head = NULL;
	dll->m_data_size = data_size;
	dll->m_size = 0;

	return dll;
}

void dll_destroy(s_doubly_linked_list_t *dll) {
	s_node_t *curr_node = dll->m_head;
	s_node_t *next_node;
	for (size_t i = 0; i < dll->m_size; i++) {
		next_node = (s_node_t *) curr_node->m_next;
		node_destory(curr_node);
		curr_node = next_node;
	}

	free(dll);
}

void dll_light_destroy(s_doubly_linked_list_t *dll) {
	s_node_t *curr_node = dll->m_head;
	s_node_t *next_node;
	for (size_t i = 0; i < dll->m_size; i++) {
		next_node = (s_node_t *) curr_node->m_next;
		node_destory(curr_node);
		curr_node = next_node;
	}

	free(dll);
}

int8_t dll_is_empty(s_doubly_linked_list_t *dll) {
	if (dll->m_size == 0) {
		return 1;
	}

	return 0;
}

s_node_t *dll_get_node(s_doubly_linked_list_t *dll, size_t pos) {
	if (dll->m_size == 0 || pos >= dll->m_size) {
		return NULL;
	}

	s_node_t *curr_node = dll->m_head;
	for (size_t i = 1; i <= pos; i++) {
		curr_node = (s_node_t *) curr_node->m_next;
	}

	return curr_node;
}

void dll_insert_first(s_doubly_linked_list_t *dll, s_node_t *node) {
	// s_node_t *new_node = node_create(dll->m_data_size, data);

	node->m_next = dll->m_head;
	if (dll->m_size != 0) {
		dll->m_head->m_prev = node;
	}

	dll->m_head = node;

	dll->m_size++;
}

void dll_insert_last(s_doubly_linked_list_t *dll, s_node_t *node) {
	// s_node_t *new_node = node_create(dll->m_data_size, data);

	s_node_t *curr_node = dll_get_node(dll, dll->m_size - 1);
	// DIE(curr_node == NULL, "Index out of range");

	if (dll->m_size == 0) {
		dll->m_head = node;
	}
	else {
		curr_node->m_next = node;
	}
	node->m_prev = curr_node;

	dll->m_size++;
}

void dll_insert(s_doubly_linked_list_t *dll, size_t pos, s_node_t *node) {
	if (pos == 0) {
		dll_insert_first(dll, node);
		return;
	}

	if (pos >= dll->m_size) {
		dll_insert_last(dll, node);
		return;
	}

	// s_node_t *new_node = node_create(dll->m_data_size, data);

	s_node_t *curr_node = dll_get_node(dll, pos);
	DIE(curr_node == NULL, "Index out of range");

	curr_node->m_prev->m_next = node;
	node->m_prev = curr_node->m_prev;

	curr_node->m_prev = node;
	node->m_next = curr_node;

	dll->m_size++;
}

// void dll_insert_node(s_doubly_linked_list_t *dll, s_node_t *node, size_t pos) {
// 	dll_insert(dll, pos, node->m_data);

// 	node_destory(node);
// }

void dll_insert_by_addr(s_doubly_linked_list_t *dll, s_node_t *node) {
	if (dll_is_empty(dll)) {
		dll_insert(dll, 0, node);
		return;
	}

	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size && curr_node->m_virtual_addr < node->m_virtual_addr) {
		curr_node = curr_node->m_next;
		idx++;
	}

	dll_insert(dll, idx, node);
}

void dll_insert_by_size(s_doubly_linked_list_t *dll, s_node_t *node) {
	if (dll_is_empty(dll)) {
		dll_insert(dll, 0, node);
		return;
	}

	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size && curr_node->m_size < node->m_size) {
		curr_node = curr_node->m_next;
		idx++;
	}

	dll_insert(dll, idx, node);
}

s_node_t *dll_remove_first(s_doubly_linked_list_t *dll) {
	if (dll_is_empty(dll)) {
		return NULL;
	}

	s_node_t *node = dll->m_head;
	dll->m_head = dll->m_head->m_next;

	dll->m_size--;

	return node;
}

s_node_t *dll_remove_last(s_doubly_linked_list_t *dll) {
	if (dll_is_empty(dll)) {
		return NULL;
	}

	s_node_t *node = dll_get_node(dll, dll->m_size - 1);
	DIE(node == NULL, "Index out of range");

	if (node == dll->m_head) {
		dll->m_head = NULL;
	}
	else {
		node->m_prev->m_next = NULL;
	}

	dll->m_size--;

	return node;
}

s_node_t *dll_remove(s_doubly_linked_list_t *dll, size_t pos) {
	// printf("\nPOS: %lld\n", pos);
	if (pos == 0) {
		return dll_remove_first(dll);
	}
	if (pos == dll->m_size - 1) {
		return dll_remove_last(dll);
	}

	s_node_t *node = dll_get_node(dll, pos);
	DIE(node == NULL, "Index out of range");

	node->m_prev->m_next = node->m_next;
	node->m_next->m_prev = node->m_prev;
	dll->m_size--;

	return node;
}

s_node_t *dll_remove_by_addr(s_doubly_linked_list_t *dll, size_t addr) {
	if (dll_is_empty(dll)) {
		return NULL;
	}

	s_node_t *curr_node = dll->m_head;
	curr_node = dll->m_head;
	size_t idx = 0;

	while (idx < dll->m_size - 1 && curr_node->m_virtual_addr != addr) {
		curr_node = (s_node_t *) curr_node->m_next;
		idx++;
	}

	// printf("\n%lu %lu\n", dll->m_data_size, dll->m_size);
	if (curr_node->m_virtual_addr == addr) {
		return dll_remove(dll, idx);
	}

	return NULL;
}

s_node_t *dll_remove_prev(s_doubly_linked_list_t *dll, size_t tag,
		size_t curr_addr) {

	if (dll_is_empty(dll)) {
		return NULL;
	}

	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;
	while (idx < dll->m_size - 1 && curr_node->m_tag != tag &&
			curr_node->m_virtual_addr + curr_node->m_size != curr_addr) {

		curr_node = curr_node->m_next;
		idx++;
	}

	if (curr_node->m_tag == tag) {
		return dll_remove(dll, idx);
	}

	return NULL;
}

s_node_t *dll_remove_next(s_doubly_linked_list_t *dll, size_t tag,
		size_t next_addr) {

	if (dll_is_empty(dll)) {
		return NULL;
	}

	s_node_t *curr_node = dll->m_head;
	size_t idx = 0;
	while (idx < dll->m_size - 1 && curr_node->m_tag != tag &&
			curr_node->m_virtual_addr != next_addr) {

		curr_node = curr_node->m_next;
		idx++;
	}

	if (curr_node->m_tag == tag) {
		return dll_remove(dll, idx);
	}

	return NULL;
}

