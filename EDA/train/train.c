#include <stdio.h>
#include <stdbool.h>
#include "fatal.h"
#include "stackar.h"
#include "queue.h"

/* Meter numeros de carruagems na estação A */
void entrada(ElementType X, Queue A)
{
    Enqueue(X, A);
    printf("A carruagem %d está na estação A\n", X);
}

/* Carruaguem saem da estação C */
void saida(Queue C)
{
    if (IsEmptyQueue(C))
    {
        Error("Carruagem C vazia\n");
    }
    else
    {
        printf("Carruagens: ");
        while (!IsEmptyQueue(C))
        {
            printf("%d ", Dequeue(C));
        }
        printf("\n");
    }
}

/* Carruagem sai de A e entra na zona B */
void F(Queue A, Stack B)
{
    if (IsEmptyQueue(A))
    {
        Error("Carruaguem A vazia\n");
    }
    else
    {
        ElementType Y;
        Y = Dequeue(A);
        Push(Y, B);
        printf("A carruaguem %d está na estação B\n", Y);
    }
}

/* Carruagem sai da zoba B e vai para a zona C */
void G(Stack B, Queue C)
{
    if (IsEmpty(B))
    {
        Error("Carruagem B vazia\n");
    }
    else
    {
        ElementType Z;
        Z = Pop(B);
        Enqueue(Z, C);
        printf("A carruagem %d está na estação C\n", Z);
    }
}

int main()
{
    Queue A = CreateQueue(20);
    Stack B = CreateStack(20);
    Queue C = CreateQueue(20);
    int opt = 0;
    int x = 0;
    while (opt != 4)
    {
        printf("1- Entrada; 2- A -> B; 3- B -> C; 4- Saida: ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            x++;
            entrada(x,A);
            break;
        
        case 2:
            F(A, B);
            break;

        case 3:
            G(B, C);
            break;

        case 4:
            saida(C);
            break;
        default:
            break;
        }
    }
}
