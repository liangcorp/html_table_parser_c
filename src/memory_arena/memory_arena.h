#pragma once

#include "result.h"

#define MEMORY_ARENA_CHUNK_SIZE 2046

typedef struct MemoryArena {
    unsigned int size;
    unsigned int capacity;
} MemoryArena;


Result arena_init(MemoryArena **new_memory_arena);
Result arena_expend(MemoryArena **new_memory_arena);
Result arena_alloc(MemoryArena **new_memory_arena);
Result arena_destroy(MemoryArena **new_memory_arena);
