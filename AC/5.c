#include <stdio.h>
  
int main(void)
{
    unsigned int x = 0x12345678;
    unsigned int byte = *(unsigned char *)&x;
    if (byte == 0x78)
        printf("Little endian\n");
    else
        printf("Big endian\n");
    return 0;
}