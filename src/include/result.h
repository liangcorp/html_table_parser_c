#pragma once

#include <stdbool.h>

#define RESULT_ERROR_MESSAGE_SIZE 100

typedef struct Result {
	bool is_ok;
	char error_message[RESULT_ERROR_MESSAGE_SIZE];
} Result;
