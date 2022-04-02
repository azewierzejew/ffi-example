#include <stdio.h>
#include <caml/callback.h>
#include "Safe_stub.h"

extern int fibML(int n);

int fibC(int n) {
    printf("Fib C: %d\n", n);
    if (n <= 1) {
        return n;
    }
    int hs = fibHs(n - 2);
    int ml = fibML(n - 1);
    return hs + ml;
}

int main(int argc, char **argv)
{
    int result;

    hs_init(&argc, &argv);
    caml_startup(argv);

    result = fibC(5);
    printf("Fibonacci: %d\n", result);

    caml_shutdown();
    hs_exit();

    return 0;
}