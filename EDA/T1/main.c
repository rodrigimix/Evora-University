#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main()
{
    printf("Hello world\n");
    BigInt a = big_new("-101010101");
    BigInt b = big_new("-10203050000");
    print_b(a);
    print_b(b);
    return 0;
}