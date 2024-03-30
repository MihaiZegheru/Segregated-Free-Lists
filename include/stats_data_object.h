#ifndef STATS_DATA_OBJECT_H__
#define STATS_DATA_OBJECT_H__

#include <inttypes.h>
#include <stddef.h>

/**
 * @brief Statistics for performing DUMP_MEMORY.
 *
 */
typedef struct {
	size_t m_total_mem;
	size_t m_total_alloc_mem;
	size_t m_num_free_blocks;
	size_t m_num_alloc_blocks;
	size_t m_num_malloc_calls;
	size_t m_num_frag;
	size_t m_num_free_calls;
} s_stats_data_object_t;

#endif // STATS_DATA_OBJECT_H__
