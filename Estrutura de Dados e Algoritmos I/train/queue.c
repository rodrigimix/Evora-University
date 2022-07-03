#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"
#include "stackar.h"

#define MinQueueSize (5)

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    ElementType *Array;
};

Queue inverte(Queue Q){
	Stack qi = CreateStack(20);
    while (!IsEmptyQueue(Q))
    {
        Push(Dequeue(Q), qi);
    }
    MakeEmptyQueue(Q);
    while(!IsEmpty(qi)){
        Enqueue(Pop(qi), Q);
    }
   printf("\n"); 
    return Q;
}

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
        return true;
    }
    else
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
    return sucess_x;
}

