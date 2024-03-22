#ifndef DOUBLY_LINKED_LIST_H__
#define DOUBLY_LINKED_LIST_H__

#include <stdlib.h>
#include <inttypes.h>

#include <node.h>

typedef struct {
	s_node_t *m_head;
	size_t m_data_size;
	size_t m_size;
} s_doubly_linked_list_t;

s_doubly_linked_list_t dll_create(size_t data_size) {
	s_doubly_linked_list_t dll;
	dll.m_head = NULL;
	dll.m_data_size = data_size;
	dll.m_size = 0;

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

void dll_insert_first(s_doubly_linked_list_t *dll, void *data) {
	s_node_t *new_node = node_create(dll->m_data_size, data);

	new_node->m_next = dll->m_head;
	if (dll->m_size != 0) {
		dll->m_head->m_prev = new_node;
	}

	dll->m_head = new_node;

	dll->m_size++;
}

void dll_insert_last(s_doubly_linked_list_t *dll, void *data) {
	s_node_t *new_node = node_create(dll->m_data_size, data);

	s_node_t *curr_node = dll_get_node(dll, dll->m_size - 1);
	DIE(curr_node == NULL, "Index out of range");

	if (dll->m_size == 0) {
		dll->m_head = new_node;
	}
	else {
		curr_node->m_next = new_node;
	}
	new_node->m_prev = curr_node;

	dll->m_size++;
}

void dll_insert(s_doubly_linked_list_t *dll, size_t pos, void *data) {
	if (pos == 0) {
		dll_insert_first(dll, data);
		return;
	}

	if (pos >= dll->m_size) {
		dll_insert_last(dll, data);
		return;
	}

	s_node_t *new_node = node_create(dll->m_data_size, data);

	s_node_t *curr_node = dll_get_node(dll, pos);
	DIE(curr_node == NULL, "Index out of range");

	curr_node->m_prev->m_next = new_node;
	new_node->m_prev = curr_node->m_prev;

	curr_node->m_prev = new_node;
	new_node->m_next = curr_node;

	dll->m_size++;
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

	return node;
}




#endif // DOUBLY_LINKED_LIST_H__