/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef MACROS_DEFINITIONS_H__
#define MACROS_DEFINITIONS_H__

#define MALLOC_FAILED "Failed to alloc memory\n"
#define FAILED_TO_ALLOCATE "Out of memory\n"
#define INVALID_FREE "Invalid free\n"
#define SEG_FAULT "Segmentation fault (core dumped)\n"
#define INVALID_READ "Memory has not been written\n"
#define INDEX_OUT_OF_RANGE "Index out of range\n"

#ifndef DIE
#include <errno.h>
#include <stdio.h>
#define DIE(assertion, call_description)				     \
	do {								                 \
		if (assertion) {					         \
			fprintf(stderr, "(%s, %d): ",		 \
					__FILE__, __LINE__); \
			perror(call_description);			 \
			exit(errno);					     \
		}							                 \
	} while (0)
#endif // DIE

#endif // MACROS_DEFINITIONS_H__
