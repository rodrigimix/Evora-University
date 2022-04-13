#ifndef bigInt_h
#define bigInt_h

#include <stdio.h>


BigInt big_new(char *num);
BigInt sum_b(BigInt a, BigInt b);
BigInt sub_b(BigInt a, BigInt b);
BigInt mult_b(BigInt a, BigInt b);
BigInt div_b(BigInt a, BigInt b);
BigInt mod_b(BigInt a, BigInt b);
void print_b(BigInt a);