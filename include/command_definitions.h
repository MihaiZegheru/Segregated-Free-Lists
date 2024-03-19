#ifndef COMMAND_DEFINITIONS_H__
#define COMMAND_DEFINITIONS_H__

#include <inttypes.h>

typedef struct {
	void *m_heap_start_addr;
	size_t m_list_count;
	size_t m_list_size;
	int8_t m_should_reconstitute;
} s_command_IH_t;

typedef struct {
	size_t m_size;
} s_command_M_t;

typedef struct {
	void *m_addr;
} s_command_F_t;

typedef struct {
	void *m_src;
	size_t m_size;
} s_command_R_t;

typedef struct {
	void *m_dest;
	char *m_src;
	size_t m_size;
} s_command_W_t;

typedef struct {
} s_command_DM_t;

typedef struct {
} s_command_DH_t;

#endif // COMMAND_DEFINITIONS_H__