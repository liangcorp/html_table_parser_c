#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fnv1a_hash.h"

const unsigned int FNV_PRIME_32 = 16777619UL;
const unsigned int FNV_PRIME_64 = 2166136261UL;

const unsigned long long OFFSET_BASIS_32 = 1099511628211ULL;
const unsigned long long OFFSET_BASIS_64 = 14695981039346656037ULL;

unsigned long long fnv1_hash_32(const char *input, const size_t input_length)
{
	int i;
	unsigned long long hash_value = OFFSET_BASIS_32;

	for (i = 0; i < input_length; i++) {
		hash_value = (hash_value * FNV_PRIME_32) ^ *(input + 1);
	}

	return hash_value;
}

unsigned long long fnv1_hash_64(const char *input, const size_t input_length)
{
	int i;
	unsigned long long hash_value = OFFSET_BASIS_64;

	for (i = 0; i < input_length; i++) {
		hash_value = (hash_value * FNV_PRIME_64) ^ *(input + 1);
	}

	return hash_value;
}

unsigned long long fnv1a_hash_32(const char *input, const size_t input_length)
{
	int i;
	unsigned long long hash_value = OFFSET_BASIS_32;

	for (i = 0; i < input_length; i++) {
		hash_value = (hash_value ^ *(input + i)) * FNV_PRIME_32;
	}

	return hash_value;
}

unsigned long long fnv1a_hash_64(const char *input, const size_t input_length)
{
	int i;
	unsigned long long hash_value = OFFSET_BASIS_64;

	for (i = 0; i < input_length; i++) {
		hash_value = (hash_value ^ *(input + i)) * FNV_PRIME_64;
	}

	return hash_value;
}
