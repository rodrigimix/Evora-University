#include <stdio.h>

int main() {
int x = 518;
int y = -2;
int z;
printf("%p\n%p\n%p\n", (void *)&x, (void *)&y, (void *)&z);
return 0;
}

/* Mostra os endreços de memória de cada variavél */