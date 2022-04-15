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

