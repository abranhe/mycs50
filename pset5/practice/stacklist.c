// stack data structure using linked list

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

stacklink *create(int n);
stacklink *push(stacklink *head, int n);
stacklink *pop(stacklink *head);

int main(void)
{
    stacklink *head = create(3);
    head = push(head, 6);
    head = push(head, 9);
    head = push(head, 12);
    head = push(head, 15);
    
    eprintf("value on top of the stack: %i\n", head->n);
    
    head = pop(head);
    eprintf("value on top of the stack: %i\n", head->n);
}

stacklink *create(int n)
{
    stacklink *new = malloc(sizeof(stacklink));
    
    if (new == NULL)
    {
        exit(1);
    }
    
    new->n = n;
    new->next = NULL;
    
    return new;
}

stacklink *push(stacklink *head, int n)
{
    stacklink *new = malloc(sizeof(stacklink));
    
    if (new == NULL)
    {
        exit(1);
    }
    
    new->n = n;
    new->next = head;
    
    return new;
}

stacklink *pop(stacklink *head)
{
    fprintf(stdout, "popping: %i\n", head->n);
    
    stacklink *trav = head;
    head = trav->next;
    
    free(trav);
    return head;
}