#include <stdio.h>
#include "stackar.h"
#include "fatal.h"

void ex3(char token);

int main(){
    char token;
    printf("Insira: ");
    token = getchar();

    switch(token){
        case '(':
        ex3(token);
        break;

        default:
        while (token != '(')
        {
            printf("Não esta a adicionar nada nas stacks\n");
            printf("Insira: ");
            token = getchar();
        }
        
        
    }
}

void ex3(char token){
    Stack Ttp = CreateStack(10);
    while (token != ')'){
        printf("Insira algo: ");
        token = getchar();
        if (token == ')')
        {
            Pop(Ttp);
            printf("Top é %c\n", Top(Ttp));        }
        else
        {
            Push(token, Ttp);
            printf("Top é %c\n", Top(Ttp));
        }
    }
}