#include <stdio.h>
#include <stdlib.h>

#ifdef F_MEMORY_DEBUG
#include "memory_debug.h" // IWYU pragma: keep
#else
#include "malloc.h"
#endif

#include "memory_arena.h"

Result arena_init(MemoryArena *memory_arena, size_t size)
{
	int i;
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	memory_arena->arena_head = malloc(size * NO_OF_ELEMENT);
	if (memory_arena->arena_head == NULL) {
		result.is_ok = false;
		snprintf(result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			 "ERROR: Failed to allocate memory for arena");
		return result;
	}
	memset(memory_arena->arena_head, '\0', NO_OF_ELEMENT * size);

	memory_arena->element_size = size;
	memory_arena->occupancy = 0;
	memory_arena->arena_frontier_index = 0;
	memory_arena->has_gap = false;
	memory_arena->gap_index = 0;
	memory_arena->next_arena_head = NULL;

	for (i = 0; i < NO_OF_ELEMENT; i++) {
		memory_arena->element_list[i] = (char *)memory_arena->arena_head + i * size;
#ifdef F_PRINT_DEBUG
		printf("%p\n", memory_arena->element_list[i]);
#endif
	}

	for (i = 0; i < NO_OF_ELEMENT; i++) {
		memory_arena->occupancy_list[i] = NULL;
	}

	return result;
}

void *arena_alloc(MemoryArena *memory_arena)
{
	Result result;

	// if (memory_arena->occupancy >= NO_OF_ELEMENT * CAPACITY_THRESHOLD) {
	result = arena_expand(memory_arena);

	if (!result.is_ok) {
		printf("%s\n", result.error_message);
		abort();
	}
	// }

	void *allocated_address = NULL;
	int starting_index = (!memory_arena->has_gap) ? memory_arena->arena_frontier_index :
							memory_arena->gap_index;

	for (int i = starting_index; i < NO_OF_ELEMENT; i++) {
		if (memory_arena->occupancy_list[i] == NULL) {
			allocated_address = memory_arena->element_list[i];
			memory_arena->occupancy_list[i] = memory_arena->element_list[i];
			memory_arena->occupancy++;
			memory_arena->arena_frontier_index = i;
			break;
		}
	}

	return allocated_address;
}

Result arena_free(MemoryArena *memory_arena, void *head_ptr);

Result arena_expand(MemoryArena *memory_arena)
{
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	if (memory_arena == NULL) {
		result.is_ok = false;
		snprintf(
			result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			"ERROR: NULL memory arena passed to function: arena_expand at line %u in file %s",
			__LINE__, __FILE__);
		return result;
	}

	MemoryArena *current_arena = memory_arena;

	while (current_arena->next_arena_head != NULL) {
		current_arena = current_arena->next_arena_head;
	}

	current_arena->next_arena_head = malloc(sizeof(MemoryArena));
	memset(current_arena->next_arena_head, 0, sizeof(MemoryArena));

	return result;
}

Result arena_destroy(MemoryArena *memory_arena)
{
	Result result;

	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	if (memory_arena == NULL) {
		result.is_ok = false;
		snprintf(
			result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			"ERROR: NULL memory arena passed to function: arena_destroy at line %u in file %s",
			__LINE__, __FILE__);
		return result;
	}

	MemoryArena *to_be_freed = NULL;
	MemoryArena *current_arena = memory_arena->next_arena_head;

	while (current_arena != NULL) {
		to_be_freed = current_arena;
		current_arena = current_arena->next_arena_head;
		free(to_be_freed);
	}

	free(memory_arena->arena_head);

	return result;
}
