#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main(int argc, const char *argv[])
{
    printf("Hello, World\n");
    BigInt a = big_new("10");
    BigInt b = big_new("5");
    printf("a = ");
    print_b(a);
    printf("b = ");
    print_b(b);
    BigInt soma = div_b(a,b);
    printf("soma = ");
    print_b(soma);
    return 0;
}