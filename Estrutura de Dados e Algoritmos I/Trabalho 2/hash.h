#include <stdbool.h>

typedef char ElementType2;

#ifndef _HashLin_H
#define _HashLin_H


typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable CreateHash(int Tablesize);
void DestroyTBL(HashTable H);

bool Find(ElementType2 *Key ,HashTable H);

void Insert(ElementType2 *Key, HashTable H);

ElementType2* Retrieve_Hash(Position P, HashTable H);

HashTable Rehash(HashTable H);

void PrintTable(HashTable H);

int TableSize(HashTable H);

float LoadFactor(HashTable H);
#endif