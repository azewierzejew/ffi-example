/* Generic types and functions for generating stubs. */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

/* alloc_string is opaue to prevent modification of data. */
struct alloc_string;

/* Represents immutable string that can be shared between languages. */
typedef struct alloc_string *alloc_string_ptr;

alloc_string_ptr alloc_string_new(size_t size, const char *data);

size_t alloc_string_get_size(alloc_string_ptr string);

/* Peek a chunk of string data. */
typedef uint64_t peek_data_t;
peek_data_t alloc_string_peek(alloc_string_ptr string, size_t byte_offset);

void alloc_string_free(alloc_string_ptr string);

#ifdef __cplusplus
}
#endif