#define _DEFAULT_SOURCE
#include "stub_lib.h"
#include <endian.h>
#include <stdio.h>
#include <string.h>

struct alloc_string {
    size_t size;
    char data[0];
};

alloc_string_ptr alloc_string_new(size_t size, const char *const_data) {
    alloc_string_ptr result;

    size_t alloc_size = sizeof(result->size) + size + 1 + sizeof(peek_data_t);
    result = malloc(alloc_size);

    if (!result) {
        // No exception handling for now.
        fprintf(stderr, "Failed to allocate string of size %zu\n", size);
        exit(1);
    }
#ifdef STUB_DEBUG
    fprintf(stderr, "Allocated %p\n", result);
#endif

    memcpy(result->data, const_data, size);
    result->data[size] = 0;

    char *end_ptr = ((char *)result) + alloc_size;
    char *str_null = &result->data[size];
    memset(str_null, 0, end_ptr - str_null);
    result->size = size;

    return result;
}

size_t alloc_string_get_size(alloc_string_ptr string) { return string->size; }

peek_data_t alloc_string_peek(alloc_string_ptr string, size_t byte_offset) {
    uint64_t result = le64toh(*(const peek_data_t *)&string->data[byte_offset]);
#ifdef STUB_DEBUG
    fprintf(stderr, "Peeking %p at %zu data %.*s, raw 0x%016lx\n", string,
            byte_offset, 8, &string->data[byte_offset], result);
#endif
    return result;
}

void alloc_string_free(alloc_string_ptr string) {
#ifdef STUB_DEBUG
    fprintf(stderr, "Freeing %p\n", string);
#endif
    free(string);
}