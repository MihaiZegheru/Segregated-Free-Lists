#include <sf_lists.h>

s_sf_lists_t *sf_lists_create(size_t size, size_t lists_size,
							  size_t virtual_addr, __s8 should_reconstitute)
{
	s_sf_lists_t *sf_lists = (s_sf_lists_t *)malloc(sizeof(s_sf_lists_t));
	DIE(!sf_lists, MALLOC_FAILED);

	sf_lists->m_size = (1ull << (size + 2)) + 1;

	sf_lists->m_dll_array =
			(s_doubly_linked_list_t **)malloc(sf_lists->m_size *
			sizeof(s_doubly_linked_list_t *));

	DIE(!sf_lists->m_dll_array, MALLOC_FAILED);

	for (size_t i = 0; i < sf_lists->m_size; i++)
		sf_lists->m_dll_array[i] = dll_create(i);

	sf_lists->m_lists_size = lists_size;
	sf_lists->m_virtual_addr = virtual_addr;
	sf_lists->m_should_reconstitute = should_reconstitute;

	return sf_lists;
}

void sf_lists_destroy(s_sf_lists_t *sf_lists)
{
	for (size_t i = 0; i < sf_lists->m_size; i++)
		dll_destroy(sf_lists->m_dll_array[i]);

	free(sf_lists->m_dll_array);
	free(sf_lists);
}

__u8 sf_lists_insert(s_sf_lists_t *sf_lists, size_t data_size, s_node_t *node)
{
	if (!sf_lists->m_should_reconstitute) {
		dll_insert_by_addr(sf_lists->m_dll_array[data_size], node);
		return 0;
	}
	size_t tag = node->m_tag;

	s_doubly_linked_list_t *dll;
	s_node_t *other_node;
	__u8 found = 0;
	for (size_t i = 0; i < sf_lists->m_size; i++) {
		dll = sf_lists->m_dll_array[i];

		other_node = dll_remove_next(dll, tag, node->m_virtual_addr +
				node->m_size);

		if (other_node) {
			found++;
			size_t new_addr;
			if (other_node->m_virtual_addr < node->m_virtual_addr)
				new_addr = other_node->m_virtual_addr;
			else
				new_addr = node->m_virtual_addr;

			node->m_size = node->m_size + other_node->m_size;
			node->m_virtual_addr = new_addr;
			node->m_next = NULL;
			node->m_prev = NULL;

			node_destory(other_node);
			i = 0;
			continue;
		}

		other_node = dll_remove_prev(dll, tag, node->m_virtual_addr);
		if (other_node) {
			found++;
			size_t new_addr;
			if (other_node->m_virtual_addr < node->m_virtual_addr)
				new_addr = other_node->m_virtual_addr;
			else
				new_addr = node->m_virtual_addr;

			node->m_size = node->m_size + other_node->m_size;
			node->m_virtual_addr = new_addr;
			node->m_next = NULL;
			node->m_prev = NULL;

			node_destory(other_node);
			i = 0;
			continue;
		}
	}

	dll_insert_by_addr(sf_lists->m_dll_array[node->m_size], node);

	return found;
}

e_error_type_t sf_lists_top(s_sf_lists_t *sf_lists, s_node_t **out_node,
							size_t *out_node_size, size_t data_size)
{
	s_doubly_linked_list_t *dll;
	s_node_t *node;

	for (size_t i = data_size; i < sf_lists->m_size; i++) {
		dll = sf_lists->m_dll_array[i];
		node = dll_remove_first(dll);

		if (node) {
			*out_node = node;
			*out_node_size = i;
			return ET_NONE;
		}
	}

	return ET_EMPTY;
}

e_error_type_t sf_list_remove_by_addr(s_sf_lists_t *sf_lists,
									  s_node_t **out_node,
									  size_t *out_node_size, size_t addr)
{
	s_doubly_linked_list_t *dll;
	s_node_t *node;
	for (size_t i = 0; i < sf_lists->m_size; i++) {
		dll = sf_lists->m_dll_array[i];
		node = dll_remove_by_addr(dll, addr);

		if (node) {
			*out_node = node;
			*out_node_size = i;
			return ET_NONE;
		}
	}

	return ET_INVALID_FREE;
}
