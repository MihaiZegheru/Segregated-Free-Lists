#include <stdio.h>
#include <command.h>

int main(void) {
	printf("Hello world!");

	u_command_t cmd;
	command_read(&cmd);

	printf("%lld\n", cmd.m_IH_cmd.m_heap_start_addr);
	printf("%lld\n", cmd.m_IH_cmd.m_list_count);
	printf("%lld\n", cmd.m_IH_cmd.m_list_size);
	printf("%u\n", cmd.m_IH_cmd.m_should_reconstitute);
	return 0;
}