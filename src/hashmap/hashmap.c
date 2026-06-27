#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#ifdef F_MEMORY_DEBUG
#include "memory_debug.h" // IWYU pragma: keep
#else
#include "malloc.h"
#endif

/*
   Initiate HashMap (HashMap and Bucket)
*/
Result hashmap_init(HashMap **new_hashmap)
{
	int i;
	Result result;
	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	*new_hashmap = NULL;
	*new_hashmap = calloc(1, sizeof(HashMap));

	if (*new_hashmap == NULL) {
		result.is_ok = false;
		snprintf(result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			 "ERROR: Failed to allocate memory for HashMap");
		return result;
	}

	(*new_hashmap)->capacity_of_buckets = HASHMAP_INIT_CAPACITY;
	(*new_hashmap)->no_of_nodes = 0;
	(*new_hashmap)->bucket_occupancy = 0;
	(*new_hashmap)->head_bucket_ptr = calloc(HASHMAP_INIT_CAPACITY, sizeof(BucketArena));

	for (i = 0; i < HASHMAP_INIT_CAPACITY; i++) {
		((*new_hashmap)->head_bucket_ptr + i)->size = 0;
		((*new_hashmap)->head_bucket_ptr + i)->head_node_ptr = NULL;
	}

	return result;
}

Result hashmap_put(HashMap *hashmap, const unsigned int key, void *value)
{
	/*
       @TODO Adding a new node to the bucket.
       If bucket capacity is full, allocate new bucket of size 16
       Else calculate index number based on current bucket_capacity number
       if index number already filled, calculate fnv1a hash and append
       node to current index as singly linked list

       @TODO convert singly linked list to binary tree if linked list has 8 nodes
    */
	Result result;
	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	// Node new_node;
	// new_node.key = key;
	// new_node.value = value;

	if (hashmap->bucket_occupancy >=
	    hashmap->capacity_of_buckets * HASHMAP_OCCUPANCY_THRESHOLD) {
		hashmap_expand(&hashmap);
	}

	printf("%d, %s\n", key, (char *)value);

	return result;
}

Result hashmap_expand(HashMap **hashmap)
{
	unsigned int i;
	unsigned int new_capacity_for_buckets = 0;
	Result result;
	result.is_ok = true;
	memset(result.error_message, '\0', RESULT_ERROR_MESSAGE_SIZE);

	new_capacity_for_buckets = (*hashmap)->capacity_of_buckets + HASHMAP_INIT_CAPACITY;

	BucketArena *new_bucket_head_ptr = NULL;
	new_bucket_head_ptr = realloc((*hashmap)->head_bucket_ptr,
				      new_capacity_for_buckets * sizeof(BucketArena));

	if (new_bucket_head_ptr == NULL) {
		result.is_ok = false;
		snprintf(result.error_message, RESULT_ERROR_MESSAGE_SIZE,
			 "ERROR: Failed to allocate memory for new Buckets");
		return result;
	}

	for (i = (*hashmap)->capacity_of_buckets; i < new_capacity_for_buckets; i++) {
		(new_bucket_head_ptr + i)->size = 0;
		(new_bucket_head_ptr + i)->head_node_ptr = NULL;
	}

	(*hashmap)->head_bucket_ptr = new_bucket_head_ptr;
	(*hashmap)->capacity_of_buckets = new_capacity_for_buckets;

	return result;
}

void hashmap_print(HashMap *hashmap)
{
	unsigned int i;
	printf("Current hashmap capacity for buckets: %d\n", hashmap->capacity_of_buckets);
	printf("Current hashmap bucket occupancy: %d\n", hashmap->bucket_occupancy);

	for (i = 0; i < hashmap->capacity_of_buckets; i++) {
		if ((hashmap->head_bucket_ptr + i)->head_node_ptr != NULL)
			printf("[%d]: %d\n", i,
			       *(int *)((hashmap->head_bucket_ptr + i)->head_node_ptr->value));
		else
			printf("[%d]: empty bucket\n", i);
	}
}

void hashmap_destroy(HashMap *hashmap)
{
	unsigned int i;

	Node *temp_head_node_ptr = NULL;
	Node *to_be_free_node_ptr = NULL;

	for (i = 0; i < hashmap->capacity_of_buckets; i++) {
		temp_head_node_ptr = (hashmap->head_bucket_ptr + i)->head_node_ptr;

		if (temp_head_node_ptr == NULL)
			continue;

		while (temp_head_node_ptr->next_node_ptr != NULL) {
			to_be_free_node_ptr = temp_head_node_ptr;
			temp_head_node_ptr = temp_head_node_ptr->next_node_ptr;
			free(to_be_free_node_ptr);
		}
		free(temp_head_node_ptr);
	}

	free(hashmap->head_bucket_ptr);
	free(hashmap);
}
