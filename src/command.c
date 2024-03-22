#include <command.h>

e_error_type_t command_factory(u_command_t *ptr, size_t params_num,
		char buffer[][MAX_LINE_SIZE]) {

	e_command_type_t command_type = command_definitions_get_command_type(buffer[0]);

	size_t required_params_num = command_definitions_get_number_of_params(command_type);

	if (params_num != required_params_num) {
		// return an err here
		return -1;
	}

	ptr->m_default_cmd.command_type = command_type;
	command_definitions_construct_command(ptr, buffer);

	return ET_NONE;
}

// e_error_type_t command_destroy(void *command_ptr, e_command_type_t command_type) {

// }

e_error_type_t command_read(u_command_t *ptr) {
	char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE];
	printf("BBB");
	size_t params_num = input_handler_read_command_line(buffer);
printf("AAA");
	return command_factory(ptr, params_num, buffer);
}