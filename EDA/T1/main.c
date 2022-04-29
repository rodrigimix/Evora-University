#include <stdio.h>
#include <stdlib.h>
#include "doubleLList.h"

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
    DeleteElement(10, L);
    PrintDList("", L);
    DeleteElement(40, L);
    PrintDList("", L);
    printf("%d\n", SizeDList(L));
    printf("%d\n", IsEmptyDList(L));

    return 0;
}