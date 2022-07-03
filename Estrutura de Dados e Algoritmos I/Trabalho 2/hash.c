#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define Error(Str) FatalError(Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MinTableSize (10)

enum KindOfEntry
{
    Legitimate,
    Empty,
    Deleted
};

struct HashEntry
{
    ElementType2 Element[30];
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;


struct HashTbl
{
    int Ocupados;
    int TableSize;
    Cell *TheCells;
};


int NextPrime(int N)
{
    int x = 2;

    while (x < N)
    {
        if (N % x == 0)
        {
            N++;
            x = 1;
        }
        x++;
    }

    return N;
}

Index Hash(ElementType2 *Key, int TableSize)
{
    unsigned int HashVal = 0;

    while (*Key != '\0')
    {
        HashVal = (HashVal << 5) + *Key++;
    }
    return HashVal % TableSize;
}

float LoadFactor(HashTable H)
{
    return (float)H->Ocupados / H->TableSize;
}

void PrintTable(HashTable H)
{
    for (int i = 0; i < H->TableSize; i++)
    {
        if (H->TheCells[i].Info == Legitimate)
        {
            printf("[%s] ", H->TheCells[i].Element);
        }
        else
        {
            printf("[ ] ");
        }
    }
}

ElementType2 *Retrieve_Hash(Position P, HashTable H)
{
    return H->TheCells[P].Element;
}

int TableSize(HashTable H)
{
    return H->TableSize;
}


HashTable CreateHash(int Tablesize)
{
    HashTable H;

    if (Tablesize < MinTableSize)
    {
        Error("Table to small\n");
    }

    H = malloc(sizeof(struct HashTbl));

    if (H == NULL)
    {
        FatalError("Out of memory!\n");
    }

    H->TableSize = NextPrime(Tablesize);
    H->TheCells = malloc(sizeof(struct HashEntry) * H->TableSize);

    if (H->TheCells == NULL)
    {
        FatalError("Out of memory!\n");
    }

    for (int i = 0; i < H->TableSize; i++)
    {
        H->TheCells[i].Info = Empty;
    }

    H->Ocupados = 0;

    return H;
}

void DestroyTBL(HashTable H)
{
    free(H->TheCells);
    free(H);
}

void Insert(ElementType2 *Key, HashTable H)
{
    if (!Find(Key, H))
    {
        Position PJ = Hash(Key, H->TableSize), T = PJ;
        int OcupiedF = H->Ocupados + 1, x = 1;

        while (H->Ocupados < OcupiedF)
        {
            if (H->TheCells[T].Info == Legitimate)
            {

                T = PJ + (x*x);
                x++;

                while (T >= H->TableSize)
                {
                    T -= H->TableSize;
                }
            }
            else
            {
                strcpy(H->TheCells[T].Element, Key);
                H->TheCells[T].Info = Legitimate;
                H->Ocupados++;
            }
        }
    }
}

bool Find(ElementType2 *Key, HashTable H)
{
    for (int i = 0; i < H->TableSize; i++)
    {
        if (!strcmp(H->TheCells[i].Element, Key))
        {
            return true;
        }
    }
    return false;
}

HashTable Rehash(HashTable H)
{
    int OldSize = H->TableSize;
    Cell *OldCells = H->TheCells;

    H = CreateHash(2 * OldSize);

    for (int i = 0; i < OldSize; i++)
    {
        if (OldCells[i].Info == Legitimate)
        {
            Insert(OldCells[i].Element, H);
        }
    }

    free(OldCells);
    return H;
}