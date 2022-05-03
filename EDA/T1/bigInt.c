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

    Zero(a, b);

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
    int carry = 0, num = 0, max = 0;
    BigInt sub = malloc(sizeof(struct BigInt));
    sub->L = CreateDList();

    Zero(a, b);

    max = Max(a, b);

    printf("%d\n", max);

    if ((a->signbit == 1 && b->signbit == -1 || a->signbit == -1 && b->signbit == 1) && op != 1)
    {
        op = 2;
        if (a->signbit == -1 && b->signbit == 1)
        {
            b->signbit = -1;
        }

        return sum_b(a, b);
    }
    else
    {
        DPosition Pa = a->L->Tail->Prev;
        DPosition Pb = b->L->Tail->Prev;

        if (((a->signbit == -1 && b->signbit == 1) || (a->signbit == -1 && b->signbit == -1)) && max == 1)
        {
            while (Pa != a->L->Head || Pb != b->L->Head)
            {
                if (Retrieve(Pa) > Retrieve(Pb) && Retrieve(Pa) != 0)
                {
                    num = (10 + (Retrieve(Pb) - carry)) - Retrieve(Pa);
                    carry = 1;
                }
                else
                {
                    num = (Retrieve(Pb) - carry) - Retrieve(Pa);
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
                    num = (10 + (Retrieve(Pa) - carry)) - Retrieve(Pb);
                    carry = 1;
                }
                else
                {
                    num = (Retrieve(Pa) - carry) - Retrieve(Pb);
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

        if (((a->signbit == 1 && b->signbit == 1) || ((a->signbit == -1 && b->signbit == -1) && max == 1) || ((a->signbit == -1 && b->signbit == 1) && max == 1)))
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

void Zero(BigInt a, BigInt b)
{

    if (a->L->size > b->L->size)
    {
        while (b->L->size < a->L->size)
        {
            InsertDList(0, DHeader(b->L), b->L);
        }
    }
    else
    {
        while (a->L->size < b->L->size)
        {
            InsertDList(0, DHeader(a->L), a->L);
        }
    }
}

int Max(BigInt a, BigInt b)
{
    int max = 0;
    int count = 0;
    DPosition Ra = a->L->Head->Next;
    DPosition Rb = b->L->Head->Next;
    while (count != 1 || Ra == DFooter(a->L) || Rb == DFooter(b->L))
    {
        if (Retrieve(Ra) > Retrieve(Rb))
        {
            max = 0;
            count = 1;
        }
        else if (Retrieve(Ra) < Retrieve(Rb))
        {
            max = 1;
            count = 1;
        }
        Ra = Ra->Next;
        Rb = Rb->Next;
    }

    return max;
}

BigInt mult_b(BigInt a, BigInt b)
{
    int k = 0, i;
    BigInt mult = big_new("000");
    DPosition Pb = b->L->Tail->Prev;
    DPosition Pa = a->L->Tail->Prev;
    BigInt pro = malloc(sizeof(struct BigInt));
    pro->L = CreateDList();

    while (Pb != b->L->Head)
    {
        int c = 0, s = 0;
        if (c != 0)
        {
            InsertDList(c, DHeader(pro->L), pro->L);
        }
        while (Pa != a->L->Head)
        {
            s = (Retrieve(Pa) * Retrieve(Pb) + c) % 10;
            c = (Retrieve(Pa) * Retrieve(Pb) + c) / 10;
            InsertDList(s, DHeader(pro->L), pro->L);
            Pa = Pa->Prev;
        }
        for (i = 0; i < k; i++)
        {
            addDList(0, pro->L);
        }
        mult = sum_b(mult, pro);
        k++;
        Pb = Pb->Prev;
        Pa = a->L->Tail->Prev;
        MakeEmptyDList(pro->L);
        pro->L->size = 0;
    }

    if (a->signbit == b->signbit)
    {
        mult->signbit = 1;
    }
    else
    {
        mult->signbit = -1;
    }

    return mult;
}

BigInt div_b(BigInt a, BigInt b)
{
    BigInt ex = big_new("");
    BigInt mp = big_new("");
    BigInt pr = big_new("");
    BigInt div = big_new("");
    int i;

    for (i = 0; i < b->L->size; i++)
    {
        addDList(a->L->Head->Element, ex->L);
        a->L->Head = a->L->Head->Next;
    }

    for (i = 0; i < 10; i++)
    {
        addDList(i, mp->L);
        pr = mult_b(b, mp);
        if (Max(ex, pr) == 1)
            break;
        pr->L->Head = NULL;
        pr->L->Tail = NULL;
        mp->L->Head = NULL;
        mp->L->Tail = NULL;
        mp->L->size = 0;
        pr->L->size = 0;
    }

    pr->L->Head = NULL;
    pr->L->Tail = NULL;
    mp->L->Head = NULL;
    mp->L->Tail = NULL;

    mp->L->size = 0;
    pr->L->size = 0;

    addDList((i - 1), mp->L);
    pr = mult_b(b, mp);
    ex = sub_b(ex, pr);
    addDList(i - 1, div->L);

    pr->L->Head = NULL;
    pr->L->Tail = NULL;
    mp->L->Head = NULL;
    mp->L->Tail = NULL;

    mp->L->size = 0;
    pr->L->size = 0;

    while (a->L->Head != NULL)
    {
        addDList(a->L->Head->Element, ex->L);
        while (ex->L->Head->Element == 0)
        {
            ex->L->Head = ex->L->Head->Next;
            ex->L->size--;
        }
        for (i = 0; i < 10; i++)
        {
            addDList(i, mp->L);
            pr = mult_b(b, mp);
            if (Max(ex, pr) == 1)
                break;
            pr->L->Head = NULL;
            pr->L->Tail = NULL;
            mp->L->Head = NULL;
            mp->L->Tail = NULL;

            mp->L->size = 0;
            pr->L->size = 0;
        }

        pr->L->Head = NULL;
        pr->L->Tail = NULL;
        mp->L->Head = NULL;
        mp->L->Tail = NULL;

        mp->L->size = 0;
        pr->L->size = 0;

        addDList((i - 1), mp->L);
        pr = mult_b(b, mp);
        ex = sub_b(ex, pr);
        addDList(i - 1, div->L);

        pr->L->Head = NULL;
        pr->L->Tail = NULL;
        mp->L->Head = NULL;
        mp->L->Tail = NULL;

        mp->L->size = 0;
        pr->L->size = 0;

        addDList(i - 1, div->L);

        pr->L->Head = NULL;
        pr->L->Tail = NULL;
        mp->L->Head = NULL;
        mp->L->Tail = NULL;

        mp->L->size = 0;
        pr->L->size = 0;

        a->L->Head = a->L->Head->Next;
        printf("Modulo:");
        print_b(ex);
        printf("\n");
    }

    return div;
}