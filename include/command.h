#ifndef COMMAND_H__
#define COMMAND_H__

#include <stdlib.h>
#include <string.h>

#include <command_type.h>
#include <command_data_object.h>
#include <command_definitions.h>
#include <input_handler.h>
#include <error_type.h>

#define MAX_COMMAND_PARAMS 10

e_error_type_t command_factory(u_command_t *ptr, size_t params_num,
		char buffer[][MAX_LINE_SIZE]);
// e_error_type_t command_destroy(void *command_ptr, e_command_type_t command_type);

e_error_type_t command_read(u_command_t *ptr);

#endif // COMMAND_H__