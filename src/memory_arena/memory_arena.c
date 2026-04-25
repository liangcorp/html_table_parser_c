#include "memory_arena.h"

/*
typedef struct MemoryArena {
    unsigned int *chunk_head_array;
    size_t chunk_size;
	unsigned int occupancy;
	unsigned int capacity;
    unsigned int untouched_edge_index;
    int *start;
    bool has_free;
} MemoryArena;
*/

Result arena_init(MemoryArena *new_memory_arena, size_t arena_size)
{
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	new_memory_arena = malloc(arena_size);

	return result;
}

Result arena_expand(MemoryArena **new_memory_arena);
Result arena_alloc(MemoryArena **new_memory_arena, size_t chunk_size);
Result arena_free(MemoryArena **new_memory_arena, void *chunk_head_ptr);

void arena_destroy(MemoryArena *memory_arena)
{
	free(memory_arena);
}

int main()
{
	MemoryArena new_arena;

	arena_init(&new_arena, sizeof(int) * 100);

	arena_destroy(&new_arena);
	return 0;
}
