#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main()
{
    printf("Hello world\n");
    BigInt a = big_new("-12345678900");
    BigInt b = big_new("-10203050000");
    printf("a = ");
    print_b(a);
    printf("b = ");
    print_b(b);
    BigInt soma = sum_b(a,b);
    printf("soma = ");
    print_b(soma);
    return 0;
}