#include <stdio.h>
#include <caml/callback.h>
#include <HsFFI.h>
#include <stdbool.h>
#include <string.h>
#include "stub.h"

struct string_view *show_test(uintptr_t *x)
{
    const int buffer_size = 30;
    char *buffer = malloc(buffer_size);
    snprintf(buffer, buffer_size, "RAW %ld", *x);
    struct string_view *result = malloc(sizeof(*result));
    *result = (struct string_view){.len = strlen(buffer), .data = buffer};
    return result;
}

bool eq_test(uintptr_t *x, uintptr_t *y)
{
    return *x == *y;
}

int main(int argc, char **argv)
{
    hs_init(&argc, &argv);
    caml_startup(argv);

    struct show_eq_object x = {.show = (show_t)show_test, .eq = (eq_t)eq_test, .data = (void *)5};
    struct show_eq_object y = {.show = (show_t)show_test, .eq = (eq_t)eq_test, .data = (void *)7};

    foo_C_stub(x, y);
    foo_C_stub(x, x);

    caml_shutdown();
    hs_exit();

    return 0;
}