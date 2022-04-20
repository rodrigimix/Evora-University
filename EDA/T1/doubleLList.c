#include <stdio.h>
#include "doubleLList.h"
#include <stdbool.h>

struct DNode
{
    ElementType Element;
    DPosition Next;
    DPosition Prev;
};

struct DNode *Head = NULL;

struct DNode *Last = NULL;

struct DNode *Current = NULL;

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

void MakeEmptyDList(DList L) //REVIEW
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
    Current = Head;
    while (Current != NULL)
    {
        count++;
        Current = Current->Next;
    }
    return count;
}

DPosition DHeader(DList L)
{
    return Head;
}

DPosition DFooter(DList L)
{
    return Last;
}

int IsEmptyDList(DList L){
    if(DHeader == NULL)
        return 1; // Verdade
    return 0; // Falso
}


