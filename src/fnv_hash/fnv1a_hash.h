#pragma once

unsigned long long fnv1_hash_32(const char *data, size_t input_length);
unsigned long long fnv1_hash_64(const char *data, size_t input_length);

unsigned long long fnv1a_hash_32(const char *data, size_t input_length);
unsigned long long fnv1a_hash_64(const char *data, size_t input_length);
