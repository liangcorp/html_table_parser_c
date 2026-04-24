#pragma once

#include "result.h"

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#define MEMORY_ARENA_CHUNK_SIZE 2046

typedef struct MemoryArena {
    int start;
    int offset;

	unsigned int occupancy;
	unsigned int capacity;
} MemoryArena;

Result arena_init(MemoryArena **new_memory_arena);
Result arena_expand(MemoryArena **new_memory_arena);
Result arena_alloc(MemoryArena **new_memory_arena, size_t size);
Result arena_destroy(MemoryArena **new_memory_arena);
