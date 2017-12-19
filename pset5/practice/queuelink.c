#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

void enqueue(int n);
void dequeue();
void display();


queuelist *head = NULL;
queuelist *tail = NULL;

int main(void)
{
    enqueue(5);
    enqueue(10);
    enqueue(15);
    
    for (int i = 0; i < 5; i++)
    {
        dequeue();
    }
    
    enqueue(20);
    enqueue(3);
    
    dequeue();
    
    enqueue(100);
    enqueue(250);
    enqueue(10000);
    enqueue(88888);
    
    for (int i = 0; i < 20; i++)
    {
        dequeue();
    }
    
    display();
    
    for (int i = 0; i < 50; i++)
    {
        enqueue(i*7);
    }
    
    display();
}

void enqueue(int n)
{
    queuelist *new = malloc(sizeof(queuelist));
    if (new == NULL)
    {
        exit(1);
    }
    
    new->n = n;
    new->prev = tail;
    new->next = NULL;
    
    if (head == NULL)
    {
        head = new;
    }
    
    if (tail != NULL)
    {
        tail->next = new;
    }
    
    tail = new;
}

void dequeue()
{
    if (head == NULL)
    {
        fprintf(stderr, "Nothing to dequeue.\n");
        return;
    }
    
    queuelist *trav = head;
    
    if (head->next != NULL)
    {
        head = head->next;
        head->prev = NULL;
    }
    else
    {
        head = NULL;
    }
    
    free(trav);
}

void display()
{
    queuelist *trav = head;
    int order = 0;
    
    if (trav == NULL)
    {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }
    
    while (trav != NULL)
    {
        order++;
        fprintf(stdout, "order %i: %i\n", order, trav->n);
        trav = trav->next;
    }
}