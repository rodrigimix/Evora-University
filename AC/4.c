#include <stdio.h>
#include <stdlib.h>

unsigned int reverse_endianness(unsigned int x);

int main(){
    unsigned int x = 0x12345678;
    printf("%#x -> %#x\n", x, reverse_endianness(x));
    return 0;
}

unsigned int reverse_endianness(unsigned int x){
    unsigned int b0, b1, b2, b3;
    b0 = x >> 24; 
    b1 = (x >> 8) & 0x0000ff00;
    b2 = (x << 8) & 0x0000ff00;
    b3 = x << 24;
    return b3|b2|b1|b0;
}

//cc a.c && ./a.out - VIM