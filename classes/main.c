#include "stub.h"
#include <HsFFI.h>
#include <Rts.h>
#include <caml/callback.h>
#include <caml/gc_ctrl.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Implementation of Show for unboxed integers.
alloc_string_ptr show_test(uintptr_t *x) {
    const int buffer_size = 64;
    char buffer[buffer_size];
    snprintf(buffer, buffer_size, "RawInt (%ld)", *x);
    return alloc_string_new(strlen(buffer), buffer);
}

// Implementation of Eq for unboxed integers.
bool eq_test(uintptr_t *x, uintptr_t *y) {
    return *x == *y;
}

int main(int argc, char **argv) {

    RtsConfig rts_config = defaultRtsConfig;
    rts_config.rts_opts = "-V0 --install-signal-handlers=no";
    hs_init_ghc(&argc, &argv, rts_config);

    struct show_object a = {.show = (show_t)show_test,
                            .data = (void *)123123123};
    struct show_object b = {.show = (show_t)show_test, .data = (void *)1};

    bar_C_stub(a);
    bar_C_stub(b);

    // Testing with unboxed integers.
    struct show_eq_object x = {
        .show = (show_t)show_test, .eq = (eq_t)eq_test, .data = (void *)5};
    struct show_eq_object y = {
        .show = (show_t)show_test, .eq = (eq_t)eq_test, .data = (void *)7};

    foo_C_stub(x, y);
    foo_C_stub(x, x);

    // This runs OCaml "main" ('let _ = ...' syntax) functions.
    caml_startup_pooled(argv);

    caml_shutdown();

    hs_exit();

    return 0;
}