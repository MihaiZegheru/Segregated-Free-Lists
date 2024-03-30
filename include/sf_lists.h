#ifndef SF_LISTS_H__
#define SF_LISTS_H__

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <linux/types.h>

#include <doubly_linked_list.h>
#include <macro_definitions.h>
#include <error_type.h>

typedef struct {
    s_doubly_linked_list_t **m_dll_array;
    size_t m_size;
    size_t m_lists_size;
    size_t m_virtual_addr;
    int8_t m_should_reconstitute;
} s_sf_lists_t;

s_sf_lists_t *sf_lists_create(size_t size, size_t lists_size, size_t virtual_addr,
        int8_t should_reconstitute);
void sf_lists_destroy(s_sf_lists_t *sf_lists);

__u8 sf_lists_insert(s_sf_lists_t *sf_lists, size_t data_size, s_node_t *node);
e_error_type_t sf_lists_top(s_sf_lists_t *sf_list, s_node_t **out_node,
		size_t *out_node_size, size_t data_size);
e_error_type_t sf_list_remove_by_addr(s_sf_lists_t *sf_lists, s_node_t **out_node,
		size_t *out_node_size, size_t addr);
e_error_type_t sf_list_remove_by_tag(s_sf_lists_t *sf_lists, s_node_t **out_node,
		size_t *out_node_size, size_t tag);

#endif // SF_LISTS_H__