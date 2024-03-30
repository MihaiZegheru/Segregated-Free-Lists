#ifndef COMMAND_TYPE_H__
#define COMMAND_TYPE_H__

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
