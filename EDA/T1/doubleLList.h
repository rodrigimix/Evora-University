#ifndef doubleLList_h
#define doubleLList_h

#include <stdio.h>
typedef int ElementType;

struct DNode;
struct DListStruct;
typedef struct DNode *PtrToDNode;
typedef PtrToDNode DPosition;
typedef struct DListStruct *DList;

DList CreateDList(); //DONE
void MakeEmptyDList( DList L); //DONE
int SizeDList(DList L); //DONE
DPosition DHeader(DList L); //DONE
DPosition DFooter(DList L); //DONE
int IsEmptyDList(DList L); //DONE
void InsertDList(ElementType X, DPosition P, DList L); //DONE
void InsertDListIth(ElementType X, int i, DList L);//DONE
void addDList(ElementType X, DList L); //DONE
DPosition FindDList(ElementType e, DList L); //DONE
void DeleteElement(ElementType e, DList L); //DONE
ElementType RemoveElementAt(int i, DList L);
DPosition Advance(DPosition P); //DONE
DPosition Back(DPosition P); //DONE
ElementType Retrieve(DPosition P); //DONE
void PrintDList(char *name, DList L); //DONE

#endif /* doubleLList_h */