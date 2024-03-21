#ifndef STRING_UTILS_H__
#define STRING_UTILS_H__

#include <inttypes.h>
#include <stddef.h>

#define MAX_LINE_SIZE 100

int8_t string_utils_is_end_char(char c);
size_t string_utils_split(char *str, char split, char buffer[][MAX_LINE_SIZE]);
size_t string_utils_addr_to_uint(char *addr);
size_t string_utils_str_to_uint(char *str);
int64_t string_utils_str_to_int(char *str);


#endif // STRING_UTILS_H__