#include <stdio.h>
#include "doubleLList.h"
#include "hash.h"

void create_soup(FILE *f, int l_o, int c_o, char words[l_o][c_o], DList L);
int read_number(FILE *f, int argc);
HashTable Letter_Hash(FILE *f, HashTable H,int num, DList L);
HashTable Prefixos(HashTable H);
int Search_letter(char f_l[1], int Delta_Line, int Delta_Col, int Line, int Col,  int l_o, int c_o,char Sopa[l_o][c_o], HashTable CP, int d, HashTable Wo, DList Special);
