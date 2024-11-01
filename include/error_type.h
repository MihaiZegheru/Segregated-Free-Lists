/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef ERROR_TYPE_H__
#define ERROR_TYPE_H__

/**
 * @brief Defines a list of possible errors.
 *
 */
typedef enum {
	ET_NONE,
	ET_INVALID_COMMAND_PARAM,
	ET_EMPTY,
	ET_INVALID_FREE,
	ET_INVALID_PARAM_NUM,
} e_error_type_t;

#endif // ERROR_TYPE_H__
