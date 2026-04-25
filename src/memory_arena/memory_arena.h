#pragma once

#include <stddef.h>
#include <string.h>
#include <malloc.h>

#include "result.h"

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#define CAPACITY_THREASHOLD 0.75

typedef struct MemoryArena {
	unsigned int *chunk_head_array;
	size_t chunk_size;
	unsigned int occupancy;
	unsigned int capacity;
	unsigned int untouched_edge_index;
	bool has_free;
} MemoryArena;

Result arena_init(MemoryArena *new_memory_arena, size_t arena_size);
Result arena_expand(MemoryArena **new_memory_arena);
Result arena_alloc(MemoryArena **new_memory_arena, size_t chunk_size);
Result arena_free(MemoryArena **new_memory_arena, void *chunk_head_ptr);
void arena_destroy(MemoryArena *memory_arena);
