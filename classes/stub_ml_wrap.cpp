// C implementation for foreign stubs.

#include "stub.h"
#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct raw_data {
    value val;

    raw_data(value &_val) {
        val = _val;
        caml_register_generational_global_root(&val);
    }

    ~raw_data() {
        caml_remove_generational_global_root(&val);
    }
};

struct show_data {
    value show;
    struct raw_data data;

    show_data(value &_show, value &_val) : data(_val) {
        show = _show;
        caml_register_generational_global_root(&show);
    }

    ~show_data() {
        caml_remove_generational_global_root(&show);
    }
};

struct eq_data {
    value eq;
    struct raw_data data;

    eq_data(value &_eq, value &_val) : data(_val) {
        eq = _eq;
        caml_register_generational_global_root(&eq);
    }

    ~eq_data() {
        caml_remove_generational_global_root(&eq);
    }
};

struct show_eq_data {
    value show;
    struct eq_data data;

    show_eq_data(value &_show, value &_eq, value &_val) : data(_eq, _val) {
        show = _show;
        caml_register_generational_global_root(&show);
    }

    ~show_eq_data() {
        caml_remove_generational_global_root(&show);
    }
};

alloc_string_ptr show_show_eq(struct show_eq_data **data) {
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback((*data)->show, (*data)->data.data.val);

    size_t len = caml_string_length(res);
    alloc_string_ptr result = alloc_string_new(len, String_val(res));

    CAMLreturnT(alloc_string_ptr, result);
}

bool eq_show_eq(struct show_eq_data **data1, struct show_eq_data **data2) {
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback2((*data1)->data.eq, (*data1)->data.data.val,
                         (*data2)->data.data.val);

    CAMLreturnT(bool, Bool_val(res));
}

alloc_string_ptr show_show(struct show_data **data) {
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback((*data)->show, (*data)->data.val);

    size_t len = caml_string_length(res);
    alloc_string_ptr result = alloc_string_new(len, String_val(res));

    CAMLreturnT(alloc_string_ptr, result);
}

extern "C" void foo_ML_stub(value show, value eq, value x, value y) {
    CAMLparam4(show, eq, x, y);

    show_eq_data *x_data = new show_eq_data(show, eq, x);

    show_eq_data *y_data = new show_eq_data(show, eq, y);

    struct show_eq_object x_obj, y_obj;

    x_obj = (struct show_eq_object){
        .show = (show_t)show_show_eq, .eq = (eq_t)eq_show_eq, .data = x_data};
    y_obj = (struct show_eq_object){
        .show = (show_t)show_show_eq, .eq = (eq_t)eq_show_eq, .data = y_data};

    foo_C_stub(x_obj, y_obj);

    delete x_data;

    delete y_data;

    CAMLreturn0;
}

extern "C" void bar_ML_stub(value show, value x) {
    CAMLparam2(show, x);

    show_data *x_data = new show_data(show, x);

    struct show_object x_obj;

    x_obj = (struct show_object){.show = (show_t)show_show, .data = x_data};

    bar_C_stub(x_obj);

    delete x_data;

    CAMLreturn0;
}