#include <stdio.h>
#include <command.h>
#include <doubly_linked_list.h>
#include <app_manager.h>

int main(void) {

	setbuf(stdout, NULL);
	// printf("Hello world!");

	// u_command_t cmd;
	// command_read(&cmd);

	// printf("%lld\n", cmd.m_IH_cmd.m_heap_start_addr);
	// printf("%lld\n", cmd.m_IH_cmd.m_list_count);
	// printf("%lld\n", cmd.m_IH_cmd.m_list_size);
	// printf("%u\n", cmd.m_IH_cmd.m_should_reconstitute);
	// char v[] = "0x10B";
	// size_t a = string_utils_addr_to_uint(v);
	// printf("%llu", a);
	// return 0 ;
	app_tick();
	// s_doubly_linked_list_t *dll;
	// dll = dll_create(8);
	// int v[1];
	// v[0] = 1;

	// s_node_t *node = node_create(sizeof(int), 0, v);
	// dll_insert_first(dll, node);
	// v[0] = 4;
	// node = node_create(sizeof(int), 0, v);
	// dll_insert_first(dll, node);
	// // dll_insert_first(dll, v);
	// // // dll_remove_first(&dll);
	// // v[0] = 10;
	// // dll_insert(dll, 1, v);
	// // dll_remove(dll, 1);
	// s_node_t *a = dll_get_node(dll, 0);
	// printf("%d\n", *(int *) a->m_data);

	return 0;
}