#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <stdio.h>
#include <inttypes.h>

#include <string_utils.h>

size_t input_handler_read_command_line(char buffer[][MAX_LINE_SIZE]);

#endif // INPUT_HANDLER_H__