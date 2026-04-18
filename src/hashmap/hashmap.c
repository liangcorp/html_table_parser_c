#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#ifdef F_MEMORY_DEBUG
#include "memory_debug.h"
#else
#include "malloc.h"
#endif

Result hashmap_init(HashMap **new_hashmap)
{
	int i;
	Result result;
    result.is_ok = true;
	memset(result.error_message, '\0', sizeof(result.error_message));

    *new_hashmap = NULL;
    *new_hashmap = calloc(1, sizeof(new_hashmap));

    if (*new_hashmap == NULL) {
        result.is_ok = false;
        snprintf(result.error_message, sizeof(result.error_message), "ERROR: Failed to allocate memory for HashMap");
        return result;
    }

	(*new_hashmap)->capacity = HASHMAP_INIT_CAPACITY;
	(*new_hashmap)->bucket = calloc(HASHMAP_INIT_CAPACITY, sizeof(HashMap));

	for (i = 0; i < HASHMAP_INIT_CAPACITY; i++) {
		((*new_hashmap)->bucket + i)->hash = 0;
		((*new_hashmap)->bucket + i)->key = 0;
		((*new_hashmap)->bucket + i)->value = NULL;
		((*new_hashmap)->bucket + i)->next_node_ptr = NULL;
	}

	return result;
}

Result hashmap_put(Bucket *new_bucket) {
    Result result;
    result.is_ok = true;

    return result;
}

void hashmap_print(HashMap *hashmap)
{
	int i;
	printf("Current hashmap capacity: %d\n", hashmap->capacity);
	printf("Current hashmap occupancy: %d\n", hashmap->occupancy);

	for (i = 0; i < hashmap->capacity; i++) {
		if ((hashmap->bucket + i)->value != NULL)
			printf("[%d]: %d\n", i, *(int *)((hashmap->bucket + i)->value));
		else
			printf("[%d]: empty bucket\n", i);
	}
}

void hashmap_destroy(HashMap *hashmap)
{
	free(hashmap->bucket);
	free(hashmap);
}
