#include <stdio.h>
#include "doubleLList.h"
#include <stdlib.h>
#include <stdbool.h>

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
    // if (L != NULL)
    //   DeleteList(L);
    L = malloc(sizeof(struct DListStruct));
    // if (L == NULL)
    // FatalError("Out of memory!");
    L->Head = malloc(sizeof(struct DNode));
    L->Tail = malloc(sizeof(struct DNode));
    // Null
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
        exit(1);
    }
    RT->Element = X;

    RT->Next = P->Next;
    RT->Prev = P;
    P->Next->Prev = RT;
    P->Next = RT;
    L->size++;
}

void addDList(ElementType X, DList L)
{
    DPosition PJ = DFooter(L);

    PJ = PJ->Prev;
    InsertDList(X, PJ, L);
    L->size++;
}

DPosition FindDList(ElementType e, DList L)
{
    DPosition P = DHeader(L);

    if (IsEmptyDList(L) == 1)
    {
        printf("Empty List");
        exit(1);
    }
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
    DPosition PJ;

    PJ = FindDList(e, L);

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

void MakeEmptyDList(DList L)
{
    DPosition P;
    P = L->Tail;
    while (P != NULL)
    {
        if (IsEmptyDList(L) == 1)
        {
            break;
        }

        DeleteElement(P->Element, L);
        P = P->Prev;
    }
}

int main()
{
    DList L = CreateDList();
    printf("%d\n", IsEmptyDList(L));
    PrintDList("", L);
    InsertDList(30, DHeader(L), L);
    PrintDList("", L);
    InsertDList(20, DHeader(L), L);
    PrintDList("", L);
    InsertDList(10, DHeader(L), L);
    PrintDList("", L);
    printf("%d\n", IsEmptyDList(L));
    MakeEmptyDList(L);
    PrintDList("", L);
    DeleteElement(10, L);
    PrintDList("", L);
    DeleteElement(20, L);
    PrintDList("", L);
    DeleteElement(30, L);
    PrintDList("", L);
    printf("%d\n", SizeDList(L));
    printf("%d\n", IsEmptyDList(L));

    return 0;
}
