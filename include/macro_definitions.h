#ifndef MACROS_DEFINITIONS_H__
#define MACROS_DEFINITIONS_H__

#define FAILED_TO_ALLOCATE "Failed to allocate memory."

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

#endif // MACROS_DEFINITIONS_H__