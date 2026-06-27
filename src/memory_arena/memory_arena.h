#pragma once

#include <stddef.h>
#include <string.h>

#include "result.h"

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#define CAPACITY_THRESHOLD 0.75
#define NO_OF_ELEMENT 100

typedef struct MemoryArena {
	void *arena_head;		     // pointer of top of arena memory allocation
	void *element_list[NO_OF_ELEMENT];   // array of pointers
	void *occupancy_list[NO_OF_ELEMENT]; // array to track if pointers were occupied
	size_t element_size;		     // size of each element
	unsigned int occupancy;		     // occupancy
	unsigned int arena_frontier_index;   // index of first empty element
	bool has_gap;			     // does the element_list has empty gap
	unsigned int gap_index;		     // position of the first gap
	struct MemoryArena *next_arena_head; // next arena pointer
} MemoryArena;

Result arena_init(MemoryArena *memory_arena, size_t element_size);
void *arena_alloc(MemoryArena *memory_arena);
Result arena_free(MemoryArena *memory_arena, void *head_ptr);
Result arena_expand(MemoryArena *memory_arena);
Result arena_destroy(MemoryArena *memory_arena);
