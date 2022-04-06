// Stubs in C callable from language specific stubs.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stub_lib.h"
#include <stdbool.h>
#include <stdlib.h>

typedef alloc_string_ptr (*show_t)(void **);
typedef bool (*eq_t)(void **, void **);

struct show_eq_object {
    show_t show;
    eq_t eq;
    void *data;
};

struct show_object {
    show_t show;
    void *data;
};

extern void foo_C_stub(struct show_eq_object x, struct show_eq_object y);

extern void bar_C_stub(struct show_object x);

#ifdef __cplusplus
}
#endif