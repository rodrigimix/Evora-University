#include <stdio.h>
#include "find_letter.h"
#include "doubleLList.h"
#include <string.h>
#include "hash.h"

int main(int argc, char *argv[])
{
    DList special = CreateDList();
    FILE *f;
    f = fopen(argv[1], "r");
    int lenght = read_number(f, argc); 
    HashTable H = Letter_Hash(f, H,lenght, special);
    HashTable PJ = Prefixos(H);
    int l = read_number(f, argc);
    int c = read_number(f, argc);
    char words[l][c];
    create_soup(f, l, c, words, special);
    fclose(f);

    char f_l[1];

    int Dir[9] = {5, 6, 7, 4, 10, 0, 3, 2, 1}; // Dir[4] = nulo nao pode ser efetuado...
    int mn = 0;

    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            memset(f_l, '\0', sizeof(f_l));

           f_l[0] = words[i][j];
            int n = 0;
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    mn += Search_letter(f_l, a, b, i, j, l, c, words, PJ, Dir[n], H, special);
                    n++;
                } 
            }
        }
    }
    printf("Encontradas %d palavras\n", mn);
    return 0;
}
