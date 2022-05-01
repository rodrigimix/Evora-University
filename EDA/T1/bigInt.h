//
//  bigInt.h
//  BigInt
//
//  Created by Ligia Ferreira on 30/03/2022.
//

#ifndef bigInt_h
#define bigInt_h

#include <stdio.h>
#include "doubleLList.h"

struct BigInt;
typedef struct BigInt *BigInt;

BigInt big_new(char *num);
BigInt sum_b(BigInt a, BigInt b);
/*BigInt sub_b(BigInt a, BigInt b);
BigInt mult_b(BigInt a, BigInt b);
BigInt div_b(BigInt a, BigInt b);
BigInt mod_b(BigInt a, BigInt b);*/
void print_b(BigInt a);



#endif /* bigInt_h */