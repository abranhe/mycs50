// stack data structure using array

#include <cs50.h>
#include <stdlib.h>

#include "struct.h"

#define MAX 5


void push(stackarray *s, int n);
int pop(stackarray *s);

int main(void)
{
    stackarray num;
    num.n = malloc(sizeof(int) * MAX);
    if (num.n == NULL)
    {
        exit(1);
    }
    
    num.top = 0;
    num.max = MAX;
    
    push(&num, 5);
    push(&num, 10);
    push(&num, 15);
    push(&num, 20);
    push(&num, 25);
    push(&num, 30); //error
    
    // *num.n = 5;
    // *(num.n+1) = 10;
    
    for (int i = 0; i < MAX; i++)
    {
        eprintf("%i\n", *(num.n+i));
    }
    
    for (int i = 0, n = num.top; i < n; i++)
    {
        eprintf("popped. %i\n", pop(&num));
    }
    
    eprintf("max: %i. top: %i\n", num.max, num.top);
}

void push(stackarray *s, int n)
{
    if (s->max == s->top)
    {
        eprintf("Stack is full. Failed to insert %i.\n", n);
        return;
    }
    
    // s is a pointer, to use -> to get the value of n (which is another pointer) inside s
    // s->n is a pointer, hence to use dereference * to change the value inside s->n
    // +s->top is to determine the order of the array of integers
    *(s->n+s->top) = n;
    s->top = s->top + 1;
}

int pop(stackarray *s)
{
    if (s->top == 0)
    {
        eprintf("Nothing to pop.\n");
        return 0;
    }
    
    s->top = s->top - 1;
    return *(s->n+s->top); 
}