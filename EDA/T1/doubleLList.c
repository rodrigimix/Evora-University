#include <stdio.h>
#include "doubleLList.h"
#include <stdbool.h>

struct DNode
{
    ElementType Element;
    DPosition Next;
    DPosition Prev;
};

DList CreateDList()
{
    DList L;
    if (L != NULL)
        DeleteList(L);
    L = malloc(sizeof(struct DNode));
    if (L == NULL)
        FatalError("Out of memory!");
    L->Next = NULL;
    return L;
}

void MakeEmptyDList(DList L)
{
    DPosition P = L;
    while (P != NULL)
    {
        Delete(P->Element, L);
        P = P->Next;
    }
}

int SizeDList(DList L)
{
    int count = 0;
    while (L != NULL)
    {
        count++;
        L = L->Next;
    }
    return count;
}

DPosition DHeader(DList L)
{
    return L;
}

DPosition DFooter(DList L)
{
    return L->Next;
}

int IsEmptyDList(DList L){
    if(DFooter == NULL)
        return 1; // Verdade
    return 0; // Falso
}

