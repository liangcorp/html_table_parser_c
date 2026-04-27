#ifdef F_MEMORY_DEBUG
#include "memory_debug.h"
#else
#include "malloc.h"
#endif

#include <stdio.h>

#include "memory_arena.h"

Result arena_init(MemoryArena *new_memory_arena, size_t size)
{
	int i;
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	new_memory_arena->arena_head = malloc(size * NO_OF_ELEMENT);
	new_memory_arena->element_size = size;
	new_memory_arena->occupancy = 0;
	new_memory_arena->arena_frontier_index = 0;
	new_memory_arena->has_freed_arena = false;

	// printf("element size: %ld\n", size);
	for (i = 0; i < NO_OF_ELEMENT; i++) {
		new_memory_arena->element_head_array[i] =
			(char *)new_memory_arena->arena_head + (size * i);
		// printf("%p\n", new_memory_arena->element_head_array[i]);
	}

	if (new_memory_arena->arena_head == NULL) {
		result.is_ok = false;
		snprintf(result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			 "ERROR: Failed to allocate memory for arena");
	}

	return result;
}

Result arena_expand(MemoryArena *new_memory_arena);

Result arena_alloc(MemoryArena *new_memory_arena, size_t element_size);

Result arena_free(MemoryArena *new_memory_arena, void *head_ptr);

Result arena_reset(MemoryArena *memory_arena)
{
	int i;
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	memory_arena->element_size = 0;
	memory_arena->occupancy = 0;
	memory_arena->arena_frontier_index = 0;
	memory_arena->has_freed_arena = false;

	for (i = 0; i < NO_OF_ELEMENT; i++) {
		memory_arena->element_head_array[i] = 0;
	}
    return result;
}

void arena_destroy(MemoryArena *memory_arena)
{
	free(memory_arena->arena_head);
}
