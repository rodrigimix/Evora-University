#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"
#include "string.h"

#define Max 100

struct BigInt
{
    char digits[100];
    int signbit;
    int lastdigit;
};

BigInt big_new(char *num)
{
    int t = 0;
    BigInt PJ = malloc(sizeof(struct BigInt));
    if (num[0] == '-')
    {
        PJ->signbit = -1;
    }
    else
    {
        PJ->signbit = 1;
    }

    for (int i = 0; i < Max; i++)
    {
        PJ->digits[i] = (char)0;
    }

    for (int x = 0; x <= strlen(num); x++)
    {
        if (num[x] == '-')
        {
            x++;
            continue;
        }


        PJ->digits[PJ->lastdigit] = num[strlen(num)-t];
        t--;
    }

    if(atoi(num) == 0){
        PJ->lastdigit = 0;
    }
    return PJ;
}

void print_b(BigInt a){
    int i;
    if (a->signbit == -1)
    {
        printf("-");
    }
    for (i= a->lastdigit; i >= 0; i--)
    {
        printf("%c", a->digits[i]);
    }
    printf("\n");
}