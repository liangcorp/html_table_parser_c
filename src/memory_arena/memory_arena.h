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
	void *arena_head;
	void *element_list[NO_OF_ELEMENT];
	void *occupancy_list[NO_OF_ELEMENT];
	size_t element_size;
	unsigned int occupancy;
	unsigned int arena_frontier_index;
	bool has_gap;
	unsigned int gap_index;
    void *next_arena_head;
} MemoryArena;

Result arena_init(MemoryArena *memory_arena, size_t element_size);
void *arena_alloc(MemoryArena *memory_arena);
Result arena_free(MemoryArena *memory_arena, void *head_ptr);
Result arena_expand(MemoryArena *memory_arena, MemoryArena *next_arena);
void arena_destroy(MemoryArena *memory_arena);
