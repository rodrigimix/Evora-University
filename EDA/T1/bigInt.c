#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"
#include "string.h"

#define Max 100

struct DNode
{
    ElementType Element;
    DPosition Next;
    DPosition Prev;
};

struct DListStruct
{
    int size;
    DPosition Head;
    DPosition Tail;
};

struct BigInt
{
    DList L;
    int signbit;
};

BigInt big_new(char *num){
    int t = 0;
    BigInt PJ = malloc(sizeof(struct BigInt));
    PJ->L = CreateDList();

    if (num[0] == '-')
    {
        PJ->signbit = -1;
    }
    else
    {
        PJ->signbit = 1;
    }

    DPosition P = DHeader(PJ->L);
    for (int i = 0; i < strlen(num); i++)
    {
        if (num[i] == '-')
        {
            continue;
        }
        

        InsertDList((int) num[i]-48, P, PJ->L);
        P = P->Next;
    }

    return PJ;
    
}

void print_b(BigInt a){
    int i;
    if (a->signbit == -1)
    {
        printf("-");
    }
    PrintDList("", a->L);
    printf("\n");
}