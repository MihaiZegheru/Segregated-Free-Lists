#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <inttypes.h>

#include <string_utils.h>

#define MAX_LINE_SIZE 100

size_t input_handler_read_line(char **buffer);

#endif // INPUT_HANDLER_H__