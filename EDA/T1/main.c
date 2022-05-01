#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"

int main()
{
    printf("Hello world\n");
    BigInt a = big_new("-101010101");
    print_b(a);

    return 0;
}