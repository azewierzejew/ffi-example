#include <stdio.h>
#include <string.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

int fibML(int n)
{
    static const value *fib_closure = NULL;
    if (fib_closure == NULL)
        fib_closure = caml_named_value("fibML");
    return Int_val(caml_callback(*fib_closure, Val_int(n)));
}

extern int fibC(int n);

value fibC_stub(value n) {
    return Val_int(fibC(Int_val(n)));
}