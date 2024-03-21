#include <stdio.h>
#include <command.h>
#include <doubly_linked_list.h>

int main(void) {
	// printf("Hello world!");

	// u_command_t cmd;
	// command_read(&cmd);

	// printf("%lld\n", cmd.m_IH_cmd.m_heap_start_addr);
	// printf("%lld\n", cmd.m_IH_cmd.m_list_count);
	// printf("%lld\n", cmd.m_IH_cmd.m_list_size);
	// printf("%u\n", cmd.m_IH_cmd.m_should_reconstitute);

	s_doubly_linked_list_t dll;
	dll = dll_create(8);
	int v[1];
	v[0] = 1;
	dll_insert_last(&dll, v);
	v[0] = 4;
	dll_insert_last(&dll, v);
	dll_remove_first(&dll);
	s_node_t *a = dll_get_node(&dll, 1);
	printf("%d\n", *(int *) a->m_data);
	return 0;
}