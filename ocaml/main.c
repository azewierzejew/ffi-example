#include <stdio.h>
#include <caml/callback.h>

extern int fibML(int n);

int fibC(int n) {
    printf("Fib C: %d\n", n);
    if (n <= 1) {
        return n;
    }
    int ml = fibML(n - 2);
    int c = fibC(n - 1);
    return ml + c;
}

int main(int argc, char **argv)
{
    int result;

    /* Initialize OCaml code */
    caml_startup(argv);

    /* Do some computation */
    result = fibML(5);
    printf("Fibonacci: %d\n", result);

    return 0;
}