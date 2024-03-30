#ifndef COMMAND_H__
#define COMMAND_H__

#include <stdlib.h>
#include <string.h>

#include <command_type.h>
#include <command_definitions.h>
#include <input_handler.h>
#include <error_type.h>

e_error_type_t command_factory(u_command_t *ptr, size_t params_num,
							   char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE]);

e_error_type_t command_read(u_command_t *ptr,
							char buffer[MAX_COMMAND_PARAMS][MAX_LINE_SIZE]);

#endif // COMMAND_H__
