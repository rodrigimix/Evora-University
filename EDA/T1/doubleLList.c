#include <stdio.h>
#include "doubleLList.h"
#include <stdlib.h>
#include <stdbool.h>
#include "bigInt.h"

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

DList CreateDList()
{
    DList L;
    L = malloc(sizeof(struct DListStruct));
    if (L == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }
    L->Head = malloc(sizeof(struct DNode));
    L->Tail = malloc(sizeof(struct DNode));
    L->size = 0;
    L->Head->Next = L->Tail;
    L->Tail->Prev = L->Head;
    return L;
}

int SizeDList(DList L)
{
    return L->size;
}
DPosition DHeader(DList L)
{
    return L->Head;
}
DPosition DFooter(DList L)
{
    return L->Tail;
}

void InsertDList(ElementType X, DPosition P, DList L)
{
    DPosition RT = malloc(sizeof(struct DNode));

    if (RT == NULL)
    {
        printf("Out of memory\n");
    }
    else
    {
        RT->Element = X;
        RT->Next = P->Next;
        RT->Prev = P;
        P->Next->Prev = RT;
        P->Next = RT;
        L->size++;
    }
}

void addDList(ElementType X, DList L)
{
    DPosition PJ = DFooter(L);

    PJ = PJ->Prev;
    InsertDList(X, PJ, L);
}

DPosition FindDList(ElementType e, DList L)
{
    DPosition P = DHeader(L);
    while (P != L->Tail)
    {
        if (P->Element == e)
        {
            return P;
        }
        P = Advance(P);
    }
    return NULL;
}

void PrintDList(char *name, DList L)
{
    printf("( ");
    DPosition P = L->Head->Next;
    while (P != L->Tail)
    {
        printf("%d ", Retrieve(P));
        P = Advance(P);
    }
    printf(" )\n");
}

ElementType Retrieve(DPosition P)
{
    return P->Element;
}

DPosition Advance(DPosition P)
{
    return P->Next;
}

DPosition Back(DPosition P)
{
    return P->Prev;
}

int IsEmptyDList(DList L)
{
    if (L->Head->Next == L->Tail)
        return 1;
    else
        return 0;
}

void DeleteElement(ElementType e, DList L)
{
    DPosition PJ = FindDList(e, L);

    if (PJ != NULL)
    {
        if (PJ == DHeader(L))
        {
            L->Head = L->Head->Next;
        }
        else
        {
            PJ->Prev->Next = PJ->Next;
        }
        if (PJ == DFooter(L))
        {
            L->Tail = PJ->Prev;
        }
        else
        {
            PJ->Next->Prev = PJ->Prev;
        }

        L->size--;
        free(PJ);
    }
}

void MakeEmptyDList(DList L)
{
    DPosition P;
    P = L->Tail;
    while (IsEmptyDList(L) != 1)
    {
        DeleteElement(P->Element, L);
        P = P->Prev;
    }
}

void InsertDListIth(ElementType X, int i, DList L)
{
    bool flag;
    int x = 0;
    DPosition RJ = L->Head;

    while (x != i)
    {
        if (IsEmptyDList(L) == 1)
        {
            printf("Empty List");
            flag = false;
            break;
        }

        if (i > L->size)
        {
            printf("Not found");
            flag = false;
            break;
        }

        RJ = RJ->Next;
        x++;
        flag = true;
    }

    if (flag == true)
    {
        InsertDList(X, RJ->Prev, L);
    }
}

ElementType RemoveElementAt(int i, DList L)
{
    DPosition PR = DHeader(L);

    if (i > L->size + 1)
    {
        printf("Not found position");
    }
    else
    {
        for (int x = 0; x != i; x++)
        {
            PR = PR->Next;
        }

        ElementType a = PR->Element;

        DeleteElement(a, L);

        return a;
    }

    return 0;
}
