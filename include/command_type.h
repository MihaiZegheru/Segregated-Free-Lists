/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef COMMAND_TYPE_H__
#define COMMAND_TYPE_H__

/**
 * @brief Defines all the commands that can be called by the user.
 *
 */
typedef enum {
	CT_NONE,
	CT_INIT_HEAP,
	CT_MALLOC,
	CT_FREE,
	CT_READ,
	CT_WRITE,
	CT_DUMP_MEMORY,
	CT_DESTROY_HEAP,
} e_command_type_t;

#endif // COMMAND_TYPE_H__
