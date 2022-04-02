
#include <HsFFI.h>
#include "Safe_stub.h"
#include <stdio.h>

int fibonacciC(int n) {
    printf("Fib C: %d\n", n);
    if (n <= 1) {
        return n;
    }
    int hs = fibonacciHs(n - 2);
    int c = fibonacciC(n - 1);
    return hs + c;
}

int main(int argc, char *argv[])
{
    int i;
    hs_init(&argc, &argv);

    i = fibonacciHs(5);
    printf("Fibonacci: %d\n", i);

    hs_exit();
    return 0;
}