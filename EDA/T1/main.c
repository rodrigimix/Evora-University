#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main(int argc, const char *argv[])
{
    printf("Hello, World\n");
    BigInt a = big_new("111");
    BigInt b = big_new("23");
    printf("a = ");
    print_b(a);
    printf("b = ");
    print_b(b);
    BigInt soma = mult_b(a,b);
    printf("soma = ");
    print_b(soma);
    return 0;
}