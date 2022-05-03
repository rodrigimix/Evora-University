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

        if ((a->signbit == -1 && b->signbit == 1) || (a->signbit == -1 && b->signbit == -1) && max == 1)
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
    int count = 1, num = 0, carry = 0, max = 0, ct, num1 = 0, n = 0, l = 0, c = 0;
    BigInt mul = malloc(sizeof(struct BigInt));
    mul->L = CreateDList();

    if (max == 0)
    {
        ct = a->L->size;
        int ar[ct][ct];
        DPosition Pa = a->L->Tail->Prev;
        DPosition Pb = b->L->Tail->Prev;

        while (Pb != b->L->Head)
        {
            if (Retrieve(a->L) + carry >= 10) // Se fosse 9 *9 com carry 8 e depois fica 9+8 = 17
            {
                while (carry != 0)
                {
                    num = Retrieve(a->L) + carry;
                    carry = num / 10;
                    num -= (carry * 10);
                    RemoveElementAt(ct,a->L);
                    InsertDListIth(num, ct, a->L);
                    Back(Pa);
                    num1 = Retrieve(Pa) + carry;
                    RemoveElementAt(ct--, a->L);
                    InsertDListIth(num1, ct-1, a->L);
                    n++;
                }
                while (n <= 0){
                    Advance(Pa);
                    ct++;
                    n--;
                }
            }

            num = (Retrieve(a->L) + carry) * Retrieve(b->L);

            if (num >= 10)
            {
                carry = num / 10;
                num -= (carry * 10);
            }
            else
            {
                carry = 0;
            }

            ar[l][c] = num;

            if (Pa = a->L->Tail)
            {
                Pa = a->L->Tail->Prev;
                Back(Pb);
                l++;
                c = l;
                ct--;
            }

            Back(Pa);
            c++;
            ct--;
        }

        c = 0;
        l = 0;
        ct = 0;
        num = 0;
        while(c != a->L->size && ar[l][c] != '\0'){

            while (ct != 1)
            {
                if (ar[l+1][c] != '\0')
                {
                    num = num +(ar[l][c] + ar[l+1][c]);
                }
                else
                {
                    if (ar[l][c] == '\n')
                    {
                        /* code */
                    }
                    
                }
                
                
            }
            
        }
    }