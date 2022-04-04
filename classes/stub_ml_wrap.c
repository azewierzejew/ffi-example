#include "stub.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>

struct show_eq_data
{
    value show, eq, val;
};

struct show_data
{
    value show, val;
};

struct string_view *show_show_eq(struct show_eq_data **data)
{
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback((*data)->show, (*data)->val);

    size_t len = caml_string_length(res);
    char *buffer = malloc(len);
    memcpy(buffer, String_val(res), len);

    struct string_view *result = malloc(sizeof(*result));
    *result = (struct string_view){.len = len, .data = buffer};

    CAMLreturnT(struct string_view *, result);
}

bool eq_show_eq(struct show_eq_data **data1, struct show_eq_data **data2)
{
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback2((*data1)->eq, (*data1)->val, (*data2)->val);

    CAMLreturnT(bool, Bool_val(res));
}

struct string_view *show_show(struct show_data **data)
{
    CAMLparam0();
    CAMLlocal1(res);
    res = caml_callback((*data)->show, (*data)->val);

    size_t len = caml_string_length(res);
    char *buffer = malloc(len);
    memcpy(buffer, String_val(res), len);

    struct string_view *result = malloc(sizeof(*result));
    *result = (struct string_view){.len = len, .data = buffer};

    CAMLreturnT(struct string_view *, result);
}

void foo_ML_stub(value show, value eq, value x, value y)
{
    CAMLparam4(show, eq, x, y);

    struct show_eq_data *x_data = malloc(sizeof(*x_data));
    x_data->show = show;
    caml_register_generational_global_root(&x_data->show);
    x_data->eq = eq;
    caml_register_generational_global_root(&x_data->eq);
    x_data->val = x;
    caml_register_generational_global_root(&x_data->val);

    struct show_eq_data *y_data = malloc(sizeof(*y_data));
    y_data->show = show;
    caml_register_generational_global_root(&y_data->show);
    y_data->eq = eq;
    caml_register_generational_global_root(&y_data->eq);
    y_data->val = y;
    caml_register_generational_global_root(&y_data->val);

    struct show_eq_object x_obj, y_obj;

    x_obj = (struct show_eq_object){.show = (show_t)show_show_eq, .eq = (eq_t)eq_show_eq, .data = x_data};
    y_obj = (struct show_eq_object){.show = (show_t)show_show_eq, .eq = (eq_t)eq_show_eq, .data = y_data};

    foo_C_stub(x_obj, y_obj);

    caml_remove_generational_global_root(&x_data->show);
    caml_remove_generational_global_root(&x_data->eq);
    caml_remove_generational_global_root(&x_data->val);
    free(x_data);

    caml_remove_generational_global_root(&y_data->show);
    caml_remove_generational_global_root(&y_data->eq);
    caml_remove_generational_global_root(&y_data->val);
    free(y_data);

    CAMLreturn0;
}

void bar_ML_stub(value show, value x)
{
    CAMLparam2(show, x);

    struct show_data *x_data = malloc(sizeof(*x_data));
    x_data->show = show;
    caml_register_generational_global_root(&x_data->show);
    x_data->val = x;
    caml_register_generational_global_root(&x_data->val);

    struct show_object x_obj;

    x_obj = (struct show_object){.show = (show_t)show_show, .data = x_data};

    bar_C_stub(x_obj);

    caml_remove_generational_global_root(&x_data->show);
    caml_remove_generational_global_root(&x_data->val);
    free(x_data);

    CAMLreturn0;
}