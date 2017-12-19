// stack data structure using linked list - better alternative using global variable for stacklink

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

void push(int n);
int pop();

stacklink *head = NULL;

int main(void)
{
    for (int i = 3; i <= 15; i = i+3)
    {
        push(i);
    }
    
    eprintf("value on top of the stack: %i\n", head->n);
    
    eprintf("popping %i\n", pop());
    eprintf("value on top of the stack: %i\n", head->n);
    
    for (int i = 0; i < 5; i++)
    {
        eprintf("popping %i\n", pop());
    }
}

void push(int n)
{
    stacklink *new = malloc(sizeof(stacklink));
    
    if (new == NULL)
    {
        fprintf(stderr, "Failed to mallocate.\n");
        exit(1);
    }
    
    new->n = n;
    new->next = head;
    
    head = new;
}

int pop()
{
    if (head == NULL)
    {
        fprintf(stderr, "Nothing to pop.\n");
        return 0;
    }
    
    int popvalue = head->n;
    
    stacklink *trav = head;
    head = head->next;
    
    free(trav);
    return popvalue;
}