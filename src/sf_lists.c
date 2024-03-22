#include <sf_lists.h>

s_sf_lists_t *sf_lists_create(size_t size, size_t lists_size, size_t virtual_addr,
        int8_t should_reconstitute) {

    s_sf_lists_t *sf_lists = (s_sf_lists_t *) malloc(sizeof(s_sf_lists_t));
    DIE(sf_lists == NULL, FAILED_TO_ALLOCATE);

    sf_lists->m_dll_array = (s_doubly_linked_list_t **) malloc((1 << (size - 1)) *
            sizeof(s_doubly_linked_list_t *));
    DIE(sf_lists->m_dll_array == NULL, FAILED_TO_ALLOCATE);

    for (size_t i = 0; i < (1ull << (size - 1)); i++) {
        sf_lists->m_dll_array[i] = dll_create(1 << (3 + i));
    }

    sf_lists->m_size = (1 << (size - 1));
    sf_lists->m_lists_size = lists_size;
    sf_lists->m_virtual_addr = virtual_addr;
    sf_lists->m_should_reconstitute = should_reconstitute;

    return sf_lists;
}

void sf_lists_destroy(s_sf_lists_t *sf_lists) {
    for (size_t i = 0; i < sf_lists->m_size; i++) {
        dll_destroy(sf_lists->m_dll_array[i]);
    }
    free(sf_lists);
}

// static void sf_list_insert_and_join(s_sf_lists_t *sf_lists, size_t data_size, s_node_t *node) {

// }

void sf_lists_insert(s_sf_lists_t *sf_lists, size_t data_size, s_node_t *node) {
    dll_insert_by_addr(sf_lists->m_dll_array[data_size], node);
}

e_error_type_t sf_lists_remove(s_sf_lists_t *sf_list, s_node_t *out, size_t data_size) {
    s_sf_lists_t *dll;
    s_node_t *node;

    for (size_t i = data_size - 1; i < sf_list->m_size; i++) {
        dll = sf_list->m_dll_array[i];
        s_node_t *node = dll_remove_first(dll);

        if (node != NULL) {
            return ET_NONE;
        }
    }

    return ET_EMPTY;
    // CHECK IF NULL
}