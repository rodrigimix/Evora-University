#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main(int argc, const char *argv[])
{
    printf("Hello world\n");
    BigInt a = big_new("-1453778288677");
    BigInt b = big_new("8983885199936628789819168712");
    //BigInt a = big_new("13");
    //BigInt b = big_new("2");
    printf("a = ");
    print_b(a);
    printf("b = ");
    print_b(b);
    BigInt soma = sum_b(a,b);
    printf("soma = ");
    print_b(soma);
    return 0;
}