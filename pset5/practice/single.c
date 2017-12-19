#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

node* create(char c);
node* insert(node* head, char c);
bool find(node* head, char c);
int index(node* head, char c);
bool ddelete(node *head, char c);
void destroy(node *head);


int main(void)
{
    node* zw = create('z');
    zw = insert(zw, 'h');
    zw = insert(zw, 'i');
    zw = insert(zw, 'w');
    zw = insert(zw, 'e');
    zw = insert(zw, 'i');
    
    eprintf("%i\n", find(zw, 'z'));
    eprintf("%i\n", index(zw, 'z'));
    
    ddelete(zw, 'w');
    
    eprintf("%i\n", find(zw, 'w'));
    eprintf("%i\n", index(zw, 'z'));
    
    destroy(zw);
}

node* create(char c)
{
    node* new = malloc(sizeof(node));
    
    if (new == NULL)
    {
        exit(1);
    }
    
    new->c = c;
    new->next = NULL;
    return new;
}

node* insert(node* head, char c)
{
    // create a new node
    node* new = malloc(sizeof(node));
    
    // check if the node is created successfully
    if (new == NULL)
    {
        exit(1);
    }
    
    // map the new node's value to c
    new->c = c;
    
    // map the new node's next pointer to head pointer
    new->next = head;
    
    // re-map the head pointer to this new node
    return new;
}

// search c and return 1 if found, else 0
bool find(node* head, char c)
{
    // create a traveseral pointer
    node* temp = head;
    
    // iterate through temp pointer
    while (temp != NULL)
    {
        // finding c
        if (temp->c == c)
        {
            return 1;
        }
        // re-map temp pointer to next pointer
        else
        {
            temp = temp->next;
        }
    }
    
    return 0;
}

// search c and return the first matching value's index order
int index(node* head, char c)
{
    // create a traversal pointer
    node* temp = head;
    
    // declaring an index
    int index = 0;
    
    // iterate through temp pointer
    while (temp != NULL)
    {
        // increment the index number on every loop
        index++;
        
        // return the index number if c matches
        if (temp->c == c)
        {
            return index;
        }
        // re-map temp pointer to next pointer
        else
        {
            temp = temp->next;
        }
    }
    
    return 0;
}

bool ddelete(node *head, char c)
{
    // create a traversal pointer
    node* temp = head;
    
    // store previous pointer
    node* previous = head;
    
    // iterate through temp pointer
    while (temp != NULL)
    {
        // delete the index number if c matches
        if (temp->c == c)
        {
            previous->next = temp->next;
            free(temp);
            return 1;
        }
        // re-map temp pointer to next pointer
        else
        {
            previous = temp;
            temp = temp->next;
        }
    }
    
    return 0;
}

void destroy(node *head)
{
    // base case
    if (head == NULL)
    {
        return;
    }
    // recursive case
    else
    {
        destroy(head->next);
        free(head);
    }
}