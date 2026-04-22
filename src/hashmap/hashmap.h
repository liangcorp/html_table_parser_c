#pragma once

#include "result.h"

#define HASHMAP_INIT_CAPACITY 16
#define HASHMAP_OCCUPANCY_THRESHOLD 0.75
#define TREEIFY_THRESHOLD 8
#define UNTREEIFY_THRESHOLD 6

typedef struct Node {
	unsigned int hash;
	unsigned int key;
	void *value;
    struct Node *next_node_ptr;
} Node;

typedef struct Bucket {
    unsigned int size;
    struct Node *head_node_ptr;

} Bucket;

typedef struct HashMap {
	unsigned int capacity_of_buckets;
	unsigned int bucket_occupancy;
	unsigned int no_of_nodes;
	struct Bucket *bucket_head_ptr;
} HashMap;

Result hashmap_init(HashMap **new_hashmap);
void hashmap_print(HashMap *hashmap);
void hashmap_destroy(HashMap *hashmap);
Result hashmap_expand(HashMap **hashmap);
Result hashmap_put(HashMap *hashmap, const unsigned int key, void *value);
