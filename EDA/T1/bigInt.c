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

BigInt big_new(char *num)
{
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

    for (int i = 0; i < strlen(num); i++)
    {
        if (num[i] == '-')
        {
            continue;
        }

        addDList((int)num[i] - 48, PJ->L);
    }
    return PJ;
}

void print_b(BigInt a)
{
    int i;
    if (a->signbit == -1)
    {
        printf("-");
    }
    PrintDList("", a->L);
    printf("\n");
}

BigInt sum_b(BigInt a, BigInt b)
{
    int carry = 0, num = 0;
    BigInt sum = malloc(sizeof(struct BigInt));
    sum->L = CreateDList();

    if (a->L->size > b->L->size)
    {
        while (b->L->size < a->L->size)
        {
            addDList(0, b->L);
        }
    }
    else
    {
        while (a->L->size < b->L->size)
        {
            addDList(0, a->L);
        }
    }
    

    if (b->signbit == -1 && a->signbit == 1 || a->signbit == -1 && b->signbit == 1)
    {
        //vai ao subtrair
    }
    else
    {
        DPosition Pa = a->L->Tail->Prev;
        DPosition Pb = b->L->Tail->Prev;
        while (Pa != a->L->Head->Next || Pb != b->L->Head->Next)
        {
            num = Retrieve(Pa) + Retrieve(Pb) + carry;

            if (num >= 10)
            {
                num -= 10;
                carry = 1;
            }
            else{
                carry = 0;
            }

            InsertDList(num, DHeader(sum->L), sum->L);

            Pa = Back(Pa);
            Pb = Back(Pb);
        }
    }

    if(a->signbit == -1 && b->signbit == -1){
        sum->signbit = -1;
    }

    return sum;
}