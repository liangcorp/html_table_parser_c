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
	struct node *next_node_ptr;
} NodeType;

typedef struct HashMap {
	unsigned int capacity;
	unsigned int occupancy;
	NodeType *bucket;
} HashMapType;

ResultType hashmap_init(HashMapType **new_hashmap);
void hashmap_print(HashMapType *hashmap);
void hashmap_destroy(HashMapType *hashmap);
