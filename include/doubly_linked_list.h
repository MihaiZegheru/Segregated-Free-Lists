#ifndef DOUBLY_LINKED_LIST_H__
#define DOUBLY_LINKED_LIST_H__

#include <stdlib.h>
#include <inttypes.h>
#include <linux/types.h>

#include <node.h>
#include <macro_definitions.h>

typedef struct {
	s_node_t *m_head;
	size_t m_data_size;
	size_t m_size;
} s_doubly_linked_list_t;

s_doubly_linked_list_t *dll_create(size_t data_size);
void dll_destroy(s_doubly_linked_list_t *dll);
void dll_light_destroy(s_doubly_linked_list_t *dll);

int8_t dll_is_empty(s_doubly_linked_list_t *dll);
s_node_t *dll_get_node(s_doubly_linked_list_t *dll, size_t pos);

void dll_insert_first(s_doubly_linked_list_t *dll, s_node_t *node);
void dll_insert_last(s_doubly_linked_list_t *dll, s_node_t *node);
void dll_insert(s_doubly_linked_list_t *dll, size_t pos, s_node_t *node);
// void dll_insert_node(s_doubly_linked_list_t *dll, s_node_t *node, size_t pos);
void dll_insert_by_addr(s_doubly_linked_list_t *dll, s_node_t *node);
void dll_insert_by_size(s_doubly_linked_list_t *dll, s_node_t *node);

s_node_t *dll_remove_first(s_doubly_linked_list_t *dll);
s_node_t *dll_remove_last(s_doubly_linked_list_t *dll);
s_node_t *dll_remove(s_doubly_linked_list_t *dll, size_t pos);
s_node_t *dll_remove_by_addr(s_doubly_linked_list_t *dll, size_t addr);

s_node_t *dll_remove_prev(s_doubly_linked_list_t *dll, size_t tag,
		size_t curr_addr);
s_node_t *dll_remove_next(s_doubly_linked_list_t *dll, size_t tag,
		size_t next_addr);

#endif // DOUBLY_LINKED_LIST_H__
