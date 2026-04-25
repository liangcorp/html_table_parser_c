#pragma once

#include <stddef.h>
#include <string.h>

#include "result.h"

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#define CAPACITY_THREASHOLD 0.75
#define NO_OF_ELEMENT 100

typedef struct MemoryArena {
	void *element_head_array[NO_OF_ELEMENT];
	void *arena_head;
	size_t element_size;
	unsigned int occupancy;
	unsigned int arena_frontier_index;
	bool has_freed_arena;
} MemoryArena;

Result arena_init(MemoryArena *new_memory_arena, size_t size);
Result arena_expand(MemoryArena *new_memory_arena);
Result arena_alloc(MemoryArena *new_memory_arena, size_t element_size);
Result arena_free(MemoryArena *new_memory_arena, void *head_ptr);
Result arena_reset(MemoryArena *memory_arena);
void arena_destroy(MemoryArena *memory_arena);
