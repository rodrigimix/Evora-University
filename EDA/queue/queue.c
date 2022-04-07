#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"

#define MinQueueSize (5)

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    ElementType *Array;
};

/* FUNCOES AUXILIARES */
/* numero de elementos na fila */
int size(Queue Q)
{
    return (Q->Capacity - Q->Front + Q->Rear) % Q->Capacity;
}

/* indice do proximo elemento  */
int successor(int i, Queue Q)
{
    return (i + 1) % Q->Capacity;
}

/* FUNCOES DE MANIPULACAO DE QUEUES */
Queue CreateQueue(int MaxElements)
{
    Queue Q;

    if (MaxElements < MinQueueSize)
        Error("Queue size is too small");

    Q = malloc(sizeof(struct QueueRecord));
    if (Q == NULL)
        FatalError("Out of space!!!");

    Q->Array = malloc(sizeof(ElementType) * MaxElements);
    if (Q->Array == NULL)
        FatalError("Out of space!!!");

    Q->Capacity = MaxElements + 1;
    MakeEmptyQueue(Q);

    return Q;
}

void DisposeQueue(Queue Q)
{
    if (Q != NULL)
    {
        free(Q->Array);
        free(Q);
    }
}

bool IsEmptyQueue(Queue Q)
{
    if (Q->Front == Q->Rear)
    {
        printf("Empty\n");
        return true;
    }
    else
        printf("Full\n");
        return false;
}

bool IsFullQueue(Queue Q)
{
    if (Q->Capacity == Q->Rear)
    {
        return true;
    }
    else
        return false;
}

void MakeEmptyQueue(Queue Q)
{
    Q->Front = 0;
    Q->Rear = 0;
}

void Enqueue(ElementType X, Queue Q)
{
    if (size(Q) == Q->Capacity - 1)
    {
        Error("Overflow");
    }

    Q->Array[Q->Rear] = X;
    Q->Rear = successor(Q->Rear, Q);
}

ElementType Front(Queue Q)
{
    printf("Front -> %d\n", Q->Array[Q->Front]);
    return Q->Array[Q->Front];
}

ElementType Dequeue(Queue Q)
{
    int sucess_x;
    if (IsEmptyQueue(Q))
    {
        Error("Empty Queue");
    }
    sucess_x = Q->Array[Q->Front];
    Q->Front = successor(Q->Front, Q);
    printf("Ok o %d foi jogado fora\n", sucess_x);
    return sucess_x;
}

int main()
{
    int x = 0;
    int y;
    Queue Sucess = CreateQueue(20);
    while (x != 6)
    {
        printf("1- Enqueue, 2-Dequeue, 3 - Front, 4-Check Queue, 5-Make Empty, 6- Exit: ");
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            printf("Indica número: ");
            scanf("%d", &y);
            Enqueue(y, Sucess);
	    printf("\n");
            break;
        
        case 2:
            Dequeue(Sucess);
	    printf("\n");
            break;
        case 3:
            Front(Sucess);
	    printf("\n");
            break;
        case 4:
            IsEmptyQueue(Sucess);
	    printf("\n");
            break;
        case 5:
            MakeEmptyQueue(Sucess);
	    printf("\n");
            break;
        case 6:
            break;
        default:
            x = 6;
            break;
        }
    }
    return 0;
}
