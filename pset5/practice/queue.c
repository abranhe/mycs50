#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

#define MAX 10

void enqueue(queue *q, int n);
int dequeue(queue *q);

int main(void)
{
    queue q;
    q.n = malloc(sizeof(int) * MAX);
    q.front = 0;
    q.size = 0;
    
    for (int i = 0; i < 4; i++)
    {
        enqueue(&q, i);
    }
    
    for (int i = 0; i < 10; i++)
    {
        enqueue(&q, i+4);
    }
    
    for (int i = 0; i < 5; i++)
    {
        eprintf("dequeuing %i.\n", dequeue(&q));
    }
    
   for (int i = 0; i < 7; i++)
    {
        enqueue(&q, i+10);
    } 
    
    for (int i = 0; i < 3; i++)
    {
        eprintf("dequeuing %i.\n", dequeue(&q));
    }
    
    eprintf("queue front: %i, queue size: %i\n", q.front, q.size);
    
    for (int i = 0, n = q.size; i < n; i++)
    {
        int pos = (q.front + i >= MAX) ? (q.front + i) % MAX : q.front + i;
        eprintf("index %i has a value of %i\n", i, *(q.n+pos));
    }
}

void enqueue(queue *q, int n)
{
    if (q->size == MAX)
    {
        fprintf(stderr, "Queue is full.\n");
        return;
    }
    
    int next = (q->front+q->size>=MAX) ? (q->front+q->size) % MAX : q->front+q->size;
    *(q->n+next) = n;
    q->size++;
}

int dequeue(queue *q)
{
    if (q->size == 0)
    {
        fprintf(stderr, "Nothing to dequeue.\n");
        return 0;
    }
    
    int remove = *(q->n+q->front);
    q->front = (q->front + 1 == MAX) ? 0 : q->front + 1;
    q->size--;
    return remove;
}