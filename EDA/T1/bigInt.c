#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"
#include "bigInt.h"
#include "string.h"

int op = 0;

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

    if ((b->signbit == -1 && a->signbit == 1 || a->signbit == -1 && b->signbit == 1) && op != 2)
    {
        op = 1;
        return sub_b(a, b);
    }
    else
    {
        DPosition Pa = a->L->Tail->Prev;
        DPosition Pb = b->L->Tail->Prev;
        while (Pa != a->L->Head || Pb != b->L->Head)
        {
            num = Retrieve(Pa) + Retrieve(Pb) + carry;

            if (num >= 10)
            {
                num -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            InsertDList(num, DHeader(sum->L), sum->L);

            Pa = Back(Pa);
            Pb = Back(Pb);
        }
    }

    if (carry == 1)
    {
        InsertDList(carry, DHeader(sum->L), sum->L);
    }

    if (a->signbit == -1 && b->signbit == -1)
    {
        sum->signbit = -1;
    }

    return sum;
}

BigInt sub_b(BigInt a, BigInt b)
{
    int carry = 0, num = 0, size_b = 0;
    char carry_a[7], carry_b[7];
    BigInt sub = malloc(sizeof(struct BigInt));
    sub->L = CreateDList();

    if (a->L->size > b->L->size)
    {
        while (b->L->size < a->L->size)
        {
            addDList(0, b->L);
        }
    }
    else
    {
        size_b = 1;
        while (a->L->size < b->L->size)
        {
            addDList(0, a->L);
        }
    }

    if ((a->signbit == 1 && b->signbit == -1 || a->signbit == -1 && b->signbit == 1) && op != 1)
    {
        op = 2;
        return sum_b(a, b);
    }
    else
    {
        DPosition Pa = a->L->Tail->Prev;
        DPosition Pb = b->L->Tail->Prev;

        if (a->signbit == -1 && b->signbit == 1)
        {
            while (Pa != a->L->Head || Pb != b->L->Head)
            {
                if (Retrieve(Pa) < Retrieve(Pb) && Retrieve(Pa) != 0)
                {
                    num = Retrieve(Pb) - (10 + Retrieve(Pa)) + carry;
                    carry = 1;
                }
                else
                {
                    num = Retrieve(Pb) - Retrieve(Pa) - carry;
                    carry = 0;
                }
                num = abs(num);

                InsertDList(num, DHeader(sub->L), sub->L);

                Pa = Back(Pa);
                Pb = Back(Pb);
            }
        }
        else
        {
            while (Pa != a->L->Head || Pb != b->L->Head)
            {
                if (Retrieve(Pa) < Retrieve(Pb) && Retrieve(Pa) != 0)
                {
                    num = (10 + Retrieve(Pa)) - Retrieve(Pb) - carry;
                    carry = 1;
                }
                else
                {
                    num = Retrieve(Pa) - Retrieve(Pb) - carry;
                    carry = 0;
                }
                num = abs(num);

                InsertDList(num, DHeader(sub->L), sub->L);

                Pa = Back(Pa);
                Pb = Back(Pb);
            }
        }

            if (carry == 1)
            {
                InsertDList(carry, DHeader(sub->L), sub->L);
            }

            if (size_b == 1 && b->signbit == -1 && op != 1)
            {
                sub->signbit = 1;
            }
            else
            {
                sub->signbit = -1;
            }
            return sub;
        }
}