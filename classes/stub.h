#pragma once

#include <stdbool.h>
#include <stdlib.h>

struct string_view
{
    size_t len;
    char *data;
};

typedef struct string_view *(*show_t)(void **);
typedef bool (*eq_t)(void **, void **);

struct show_eq_object
{
    show_t show;
    eq_t eq;
    void *data;
};

struct show_object
{
    show_t show;
    void *data;
};

extern void foo_C_stub(struct show_eq_object x, struct show_eq_object y);

extern void bar_C_stub(struct show_object x);