#ifndef STRING_UTILS_H__
#define STRING_UTILS_H__

#include <inttypes.h>
#include <stddef.h>
#include <linux/types.h>

#define MAX_LINE_SIZE 605

/**
 * @brief Returns true if the character is line ending.
 *
 * @param c
 * @return int8_t
 */
int8_t string_utils_is_end_char(char c);

/**
 * @brief Splits a string based on the provided delimiter.
 *
 * @param str in
 * @param split
 * @param buffer out
 * @return size_t
 */
size_t string_utils_split(char *str, char split, char buffer[][MAX_LINE_SIZE]);

/**
 * @brief Converts a string of hex into uint.
 *
 * @param addr
 * @return size_t
 */
size_t string_utils_addr_to_uint(char *addr);

/**
 * @brief Converts a string to uint.
 *
 * @param str
 * @return size_t
 */
size_t string_utils_str_to_uint(char *str);

/**
 * @brief Converts a string to int.
 *
 * @param str
 * @return __s64
 */
__s64 string_utils_str_to_int(char *str);

#endif // STRING_UTILS_H__
