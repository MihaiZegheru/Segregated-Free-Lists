#ifndef COMMAND_H__
#define COMMAND_H__

#include <stdlib.h>
#include <stdarg.h>

#include <command_type.h>
#include <error_type.h>

e_error_type_t command_factory(void *command_ptr, e_command_type_t command_type, ...);
e_error_type_t command_destroy(void *command_ptr, e_command_type_t command_type);

#endif // COMMAND_H__