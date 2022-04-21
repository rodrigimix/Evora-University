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
    L->Prev = NULL;
    return L;
}

void MakeEmptyDList(DList L) // REVIEW
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

int IsEmptyDList(DList L)
{
    if (DHeader == NULL)
        return 1; // Verdade
    return 0;     // Falso
}

void InsertDList(ElementType X, DPosition P)
{
    struct DNode *PJ = (struct DNode *)malloc(sizeof(struct DNode));
    if (PJ == NULL)
    {
        FatalError("Out of space");
    }

    PJ->Element = X;

    if (IsEmptyDList == 1)
    {
        Last = PJ;
    }
    else
    {
        Head->Prev = PJ;
    }

    PJ->Next = Head;

    Head = PJ;
}

void InsertDListIth(ElementType X, int i, DList L)
{
    struct DNode *ptr;
    struct DNode *PI = (struct DNode *)malloc(sizeof(struct DNode));
    if (PI == NULL)
    {
        FatalError("Out of space\n");
    }

    PI->Element = X;
    PI->Next = NULL;
    if (i == 0)
    {
        PI->Next = Head;
        Head = PI;
    }
    else
    {
        ptr = Head;
        for (int count = 0; count < i - 1; count++)
        {
            ptr = ptr->Next;
            if (ptr == NULL)
            {
                FatalError("Position not found\n");
            }
        }

        PI->Next = ptr->Next;
        ptr->Next = PI;
    }
}

void addDList(ElementType X, DList L)
{
    struct DNode *PT = (struct DNode *)malloc(sizeof(struct DNode));
    PT->Element = X;

    if (IsEmptyDList == 1)
    {
        Last = PT;
    }
    else
    {
        Last->Next = PT;
        PT->Prev = Last;
    }

    Last = PT;
}

DPosition FindDList(ElementType e)
{
    struct DNode *ptr;
    int i = 0;
    bool flag;
    ptr = Head;
    if (ptr == NULL)
    {
        FatalError("Empty List\n");
    }

    while (ptr != NULL)
    {
        if (ptr->Element == e)
        {
            printf("Item found! Position: %d\n", i + 1);
            flag = true;
            break;
        }
        else
        {
            flag = false;
        }
        i++;
        ptr = ptr->Next;
    }

    if (!flag)
    {
        printf("Item not found\n");
    }
}

void DeleteElement(ElementType e, DList L){
    DPosition F, F1, F2;

    F = FindDList(e);
    if (F == NULL){
        F1 = F->Prev;
        F2 = F->Next;
        F1->Next = F->Next;

        if(F2 == NULL)
            F2->Prev = F->Prev;
    }
    else
        FatalError("Item not found\n");
}