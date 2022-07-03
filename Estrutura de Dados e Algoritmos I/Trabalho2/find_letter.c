#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLList.h"
#include <ctype.h>
#include "hash.h"

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

struct DNode
{
    ElementType Element;
    DPosition Next;
    DPosition Prev;
};

struct DListStruct
{
    int size;
    DPosition Head;
    DPosition Tail;
};

/*
######################################################################################################################################################################################
# Função: create_soup
# Descrição: Esta função lê o ficheiro indicado pelo utilizador e preenche os digitos do ficheiro (as letras da sopa de letras) numa matriz com as dimenções fornecidas pelo ficheiro
#
#Argumentos:
#   FILE *f - lê o ficheiro indicado pelo utilizador
#   int l_o - dimenção do sentido horizontal para a matriz words
#   int c_o - dimenção do sentido vertical para a matriz words
#   char words[][] - é a matriz onde se guarda os caracteres fornecidos pelo ficheiro
#   DList L - permite o acesso à lista duplamente ligada (L) e guardar os caracteres especiais
######################################################################################################################################################################################
*/
void create_soup(FILE *f, int l_o, int c_o, char words[l_o][c_o], DList L)
{
    int n, control = 0, pt = 0, check = 0;
    char ctr;
    for (int l = 0; l < l_o; l++)
    {
        for (int c = 0; c < c_o; c++) // Vai percorrer a linha e coluna da matriz words e vai guardar nessa matriz o caracter
        {
            n = 49;    // 49 equivale a 1 em ascii
            check = 0; // contador
            control = 0;
            DPosition P = L->Head->Next; // Repõe a DPosition na posição inicial
            fscanf(f, "%c", &ctr);       // Lê o caracter
            if (ctr == ' ')              // se o caracter lido for "espaço" ele passa para o proximo caracter
            {
                fscanf(f, "%c", &ctr);
                if ((int)ctr > 0) // Se o caracter não for especial, ele guarda esse caracter na matriz words
                {
                    words[l][c] = ctr;
                }
            }
            else if ((int)ctr < 0) // No entanto, se o caractér for especial, o procedimento é executado neste else if...
            {
                while (check != L->size) // Vai verificar na lista se existe um caracter especial
                {
                    if (Retrieve(P) == (int)ctr) // Se já existir esse caracter na lista, ele substitui esse caracter e guarda na matriz um numero index guardada na lista.
                    {
                        control = 1;
                        break;
                    }

                    P = Advance(P);
                    check++;
                    n++;
                }
                if (control == 0) // No caso da lista não corresponder ao caracter especial, ele remota ao proximo numero do caracter especial que vai trocar na matriz.
                {
                    pt++;
                    n = n + pt;
                }

                fscanf(f, "%c", &ctr);
                words[l][c - 1] = (char)n;
                fscanf(f, "%c", &ctr);
                words[l][c] = ctr;
            }
            else if (ctr == '\n')
            {
                fscanf(f, "%c", &ctr);
                words[l][c] = ctr;
            }
            else
            {
                words[l][c] = ctr;
            }
        }
    }
}

/*
######################################################################################################################################################################################
# Função: read_number
# Descrição: Esta função lê o ficheiro indicado pelo utilizador e retoma um numero indicado pelo ficheiro.
#
#Argumentos:
#   FILE *f - lê o ficheiro indicado pelo utilizador
#   int argc - verifica se o utilizador se enviou um ficheiro ao programa
#
#Retorno:
#   int n - retorna o número indicado 
######################################################################################################################################################################################
*/
int read_number(FILE *f, int argc)
{
    if (argc <= 1) // Se na execução do código não conter o ficheiro, o programa para.
    {
        printf("Insert File Error\n");
        exit(1);
    }
    else
    {
        int n;
        if (f == NULL) // Se o ficheiro não tiver nada escrito, o programa termina.
        {
            printf("Could not open file\n");
            exit(1);
        }

        fscanf(f, "%d", &n);
        return n;
    }
}

/*
######################################################################################################################################################################################
# Função: Letter_Hash
# Descrição: Esta função lê o ficheiro indicado pelo utilizador e passa as palavras-chaves da sopa de letras para uma hashtable de acesso quadrado.
#
#Argumentos:
#   FILE *f - lê o ficheiro indicado pelo utilizador
#   HashTable H - Acesso à HashTable onde vai ser guardada as palavras-chaves
#   int num - indica quantas palavras-chaves devem ser guardadas na hash
#   DList L - permite o acesso à lista duplamente ligada (L) e guardar os caracteres especiais
#
#Retorno:
#   HashTable H - retorna a HashTable modificada com as palavas-chaves inseridas
######################################################################################################################################################################################
*/
HashTable Letter_Hash(FILE *f, HashTable H, int num, DList L)
{
    H = CreateHash(num); // Cria uma hashtable de acesso quadrado
    int special_letter = 49, j = 0, z = 0, control, check, copy;
    char words[100], tmp[100]; // É usada tmp para substituir as palavras especiais por numeros e guarda-las na hashtable
    for (int n = 0; n < num; n++)
    {
        DPosition P = L->Head->Next; // Repõe a DPosition na posição inicial
        memset(words, '\0', sizeof(words)); // Reseta o array words
        memset(tmp, '\0', sizeof(tmp)); // Reseta o array tmp
        fscanf(f, "%s\n", words); // Lê uma certa linha do ficheiro e guarda no array words
        j = 0; // Index do array words
        z = 0; // Index do array tmp
        while (words[j] != '\0')
        {
            if ((int)words[j] < 0) // Se o valor em inteiro no interior do array words for inferior a 0 (-61: referência para aceder a ASCII com caracteres especiais) logo significa que possui caracteres especiais
            {
                control = 0;
                check = 0;
                copy = special_letter; // Para não perder a ordem dos numeros uso a variavel copy para guardar o último número guardado na variavel special_letter
                special_letter = 49; // 49 equivale a 1 em ascii

                while (check != L->size) // Vai verificar na lista se existe um caracter especial
                {
                    if ((int)words[j + 1] == Retrieve(P))
                    {
                        control = 1;
                        break;
                    }
                    P = Advance(P);
                    check++;
                    special_letter++;
                }
                if (control == 0)  // No caso da lista não corresponder ao caracter especial, ele guarda esse caracter (segundo digito) na lista
                {
                    addDList((int)words[j + 1], L);
                }

                tmp[z] = special_letter;
                special_letter = copy + 1;
                j++;
                z++;
            }
            else
            {
                tmp[z] = words[j];
                z++;
            }
            j++;
        }
        Insert(tmp, H); // A palavra que esta inserida no tmp vai ser guardada numa hashtable
        if (LoadFactor(H) > 0.7) // Se a HashTable tiver preenchida a 70%, cria uma nova hashtable com o doubro do tamanho. (OBS: foi escolhida 70% porque se usarmos 50% estariamos ocupar muita memoria e estes 70% preserva mais a memória)
        {
            H = Rehash(H);
        }
    }
    return H;
}

/*
######################################################################################################################################################################################
# Função: Prefixos
# Descrição: Esta função lê a hashtable onde contem as palavras-chaves e com elas cria diversos prefixos da mesma palavra e guarda numa outra hashtable.
#
#Argumentos:
#   HashTable T - Acesso à HashTable está guardada as palavras-chaves
#
#Retorno:
#   HashTable CP - retorna a HashTable modificada com os prefixos incluidos
######################################################################################################################################################################################
*/
HashTable Prefixos(HashTable T)
{
    char words[30], tmp[30];
    HashTable CP = CreateHash(TableSize(T)); // Criamos uma nova hashtable para os prefixos.

    for (int i = 0; i < TableSize(T); i++) // Verificar em todos os index da hashtable T
    {
        if (T->TheCells[i].Info == Legitimate) // Se o index tiver ocupado significa que que a palavra-chave esta dentro desse index
        {
            memset(words, '\0', sizeof(words)); // Reseta o array words
            memset(tmp, '\0', sizeof(tmp)); // Reseta o array tmp

            strcpy(words, Retrieve_Hash(i, T)); // Vai copiar tudo o que esta no index dessa hashtable e vai colar o resto no array words
            for (int j = 0; j < strlen(words) - 1; j++) // Neste processo vai ler um caracter a cada, insere no array tmp e por fim guarda na hashtable CP
            {
                tmp[j] = words[j];
                Insert(tmp, CP);
                if (LoadFactor(CP) > 0.7) // Se a HashTable tiver preenchida a 70%, cria uma nova hashtable com o doubro do tamanho. (OBS: foi escolhida 70% porque se usarmos 50% estariamos ocupar muita memoria e estes 70% preserva mais a memória)
                {
                    CP = Rehash(CP);
                }
            }
        }
    }

    return CP;
}

/*
######################################################################################################################################################################################
# Função: Search_letter
# Descrição: Esta função vai analizar a cada posição as letras presentes na sopa de letras e vai comparar com os prefixos da hashtable H e indica a posiçao dessa palavra.
#
#Argumentos:
#   
#   char f_l[1] - mostra a letra indicada pelos 2 for.
#   int Delta_line - indica o sentido onde vai analizar o array Sopa só na parte das linhas
#   int Delta_col - indica o sentido onde vai analizar o array Sopa só na parte das colunas
#   int Line - indica ao programa em posição esta a letra inicial (só na parte da linha)
#   int Col - indica ao programa em posição esta a letra inicial (só na parte da coluna)
#   int l_o - dimenção do sentido horizontal para a matriz words
#   int c_o - dimenção do sentido vertical para a matriz words
#   char Sopa[][] - matriz onde contem os caracteres da sopa de letras
#   HashTable CP - Acesso à HashTable está guardada os prefixos
#   int d - indica ao utilizador em que direção está a palavra-chave na sopa de letras
#   HashTable Wo - Acesso à HashTable está guardada as palavras-chaves
#   DList L - permite o acesso à lista duplamente ligada (L) e guardar os caracteres especiais
#
#Retorno:
#   1 ou 0 - se a palavra-chave é encontrada na sopa retora 1, senão retorna 0
######################################################################################################################################################################################
*/
int Search_letter(char f_l[1], int Delta_Line, int Delta_Col, int Line, int Col, int l_o, int c_o, char Sopa[l_o][c_o], HashTable CP, int d, HashTable Wo, DList Special)
{
    char Word[30]; // Word é um array que vai juntar as palavras na sopa de letras
    int Pos = 1, L = Line, C = Col, i, n;

    Word[0] = f_l[0]; 
    while (Find(Word, CP)) // Se a palavra feita no array Word for igual a uma das palavras do prefixo da HashTable CP, analisa a proxima posição
    {
        if (Line + Delta_Line >= 0 && Line + Delta_Line < l_o && Col + Delta_Col >= 0 && Col + Delta_Col < c_o) // Limites da sopa de letras
        {
            Word[Pos] = Sopa[Line + Delta_Line][Col + Delta_Col]; // Guarda a proxima letra no array Word
            Pos++;
            Line += Delta_Line;
            Col += Delta_Col;
        }
        else
        {
            break;
        }
    }
    if (Find(Word,Wo)) // Se a palavra feita no array Word for identica a uma das palavras-chaves na HashTable Wo, ele transmite ao utilizador a localização da palavra
    {
        printf("Palavra ");
        for (int ctt = 0; ctt < strlen(Word); ctt++) //Vai analisar os caracteres do array Word
        {
            if (isdigit(Word[ctt])) // Se um dos caracteres for um número significa que estamos parente a um caracter especial
            {
                DPosition P = Special->Head->Next; // Repoe a posição original na Lista Special
                for (i = 1; i < (int)Word[ctt] - 48; i++) // Vai ao longo da lista encontrar o digito que permite formar o caracter especial
                {
                    P = Advance(P);
                }
                printf("%c%c", (char)-61, (char)Retrieve(P)); // -61 - referência para aceder a ASCII Especial e o Retrive(P) é o caracter indicador para mostrar o caracter especial
            }

            else
            {
                printf("%c", Word[ctt]);
            }
        }
        printf(" encontrada em (%d,%d) na direção %d\n", L, C, d);
        memset(Word, '\0', sizeof(Word)); // Reseta o array Word
        return 1;
    }

    memset(Word, '\0', sizeof(Word)); // Reseta o array Word
    return 0;
}