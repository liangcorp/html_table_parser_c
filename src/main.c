#include <stdio.h>

#ifdef F_MEMORY_DEBUG

#include "memory_debug.h"

#else

#include <stdlib.h>

#endif

#include <string.h>

#include "html_table_parser.h"
#include "hashmap.h"
#include "fnv1a_hash.h"

#define HASH_SIZE 256

int main(void)
{
// 	const char *html_str = "<table><tr><td></td><td></td></tr></table>";
// 	html_tag_count_t htc = { 0, 0, 0, 0, 0, 0, 0, 0 };
// 	ResultType result = get_html_table_tag_count(&htc, html_str);
//
// 	int *test = NULL;
//
#ifdef F_MEMORY_DEBUG
	f_debug_memory_debug_init();
#endif
	//
	// 	test = calloc(1, sizeof(int));
	// 	/* 	free(test); */
	//
	// 	if (result.is_ok) {
	// 		printf("<table> count: %d\n", htc.table_head_occurrence);
	// 		printf("<tr> count: %d\n", htc.tr_head_occurrence);
	// 		printf("<th> count: %d\n", htc.th_head_occurrence);
	// 		printf("<td> count: %d\n", htc.td_head_occurrence);
	//
	// 		printf("<table> count: %d\n", htc.table_tail_occurrence);
	// 		printf("<tr> count: %d\n", htc.tr_tail_occurrence);
	// 		printf("<th> count: %d\n", htc.th_tail_occurrence);
	// 		printf("<td> count: %d\n", htc.td_tail_occurrence);
	// 	} else {
	// 		printf("%s", result.error_message);
	// 	}
	//
	// 	free(test);

	int i;
	const char *input[] = { "Hello, World!", "Hello!", ",World" };

	size_t input_array_length = sizeof(input) / sizeof(input[0]);

	for (i = 0; i < input_array_length; i++) {
		size_t length = strlen(input[i]);

		unsigned long long hash_result = fnv1a_hash_64(input[i], length);

		printf("FNV-1A Hash (64-bit): %llu\n", hash_result);
	}

	HashMap *new_hashmap = NULL;

	Result result = hashmap_init(&new_hashmap);
    char *test_str_ptr = "test";
    result = hashmap_put(new_hashmap, 10000, test_str_ptr);

	if (result.is_ok) {
		hashmap_print(new_hashmap);
	}
    else {
        printf("%s\n", result.error_message);
        printf("Program exiting with error...\n");
        return 1;
    }

	hashmap_destroy(new_hashmap);

#ifdef F_MEMORY_DEBUG
	f_debug_memory_leak_check();
	f_debug_memory_print();
#endif
	return 0;
}
