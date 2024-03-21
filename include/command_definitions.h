#ifndef COMMAND_DEFINITIONS_H__
#define COMMAND_DEFINITIONS_H__

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#ifndef DIE
#include <errno.h>
#include <stdio.h>
#define DIE(assertion, call_description)				\
        do {								\
                if (assertion) {					\
                        fprintf(stderr, "(%s, %d): ",			\
                                        __FILE__, __LINE__);		\
                        perror(call_description);			\
                        exit(errno);					\
                }							\
        } while (0)
#endif // DIE

#include <command_type.h>
#include <string_utils.h>

#define IH_PARAMS (4 + 1)
#define M_PARAMS  (1 + 1)
#define F_PARAMS  (1 + 1)
#define R_PARAMS  (2 + 1)
#define W_PARAMS  (3 + 1)
#define DM_PARAMS (0 + 1)
#define DH_PARAMS (0 + 1)

#define IH_STRING ("INIT_HEAP")
#define M_STRING  ("MALLOC")
#define F_STRING  ("FREE")
#define R_STRING  ("READ")
#define W_STRING  ("WRITE")
#define DM_STRING ("DUMP_MEMORY")
#define DH_STRING ("DESTROY_HEAP")

typedef struct {
	e_command_type_t command_type;
	size_t m_heap_start_addr;
	size_t m_list_count;
	size_t m_list_size;
	int8_t m_should_reconstitute;
} s_command_IH_t;

typedef struct {
	e_command_type_t command_type;
	size_t m_size;
} s_command_M_t;

typedef struct {
	e_command_type_t command_type;
	size_t m_addr;
} s_command_F_t;

typedef struct {
	e_command_type_t command_type;
	size_t m_src;
	size_t m_size;
} s_command_R_t;

typedef struct {
	e_command_type_t command_type;
	size_t m_dest;
	char *m_src;
	size_t m_size;
} s_command_W_t;

typedef struct {
	e_command_type_t command_type;
} s_command_DM_t;

typedef struct {
	e_command_type_t command_type;
} s_command_DH_t;

typedef struct {
	e_command_type_t command_type;
} s_default_command_t;

typedef union {
	s_default_command_t m_default_cmd;
	s_command_IH_t m_IH_cmd;
	s_command_M_t m_M_cmd;
	s_command_F_t m_F_cmd;
	s_command_R_t m_R_cmd;
	s_command_W_t m_W_cmd;
	s_command_DM_t m_DM_cmd;
	s_command_DH_t m_DH_cmd;
} u_command_t;

size_t command_definitions_get_number_of_params(e_command_type_t command_type);
e_command_type_t command_definitions_get_command_type(char *name);

void command_definitions_construct_command(u_command_t *ptr,
		char buffer[][MAX_LINE_SIZE]);

#endif // COMMAND_DEFINITIONS_H__