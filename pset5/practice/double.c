#include <cs50.h>

#include "struct.h"


dlnode *create(int n);
dlnode *insert(dlnode *head, int n);
bool search(dlnode *head, int n);
void delete(dlnode *target);
void destroy(dlnode* head);

int main(void)
{
    dlnode *nodehead = create(50);
    dlnode *zhiwei = nodehead;
    eprintf("Head pointer points to score %i.\n", nodehead->n);
    
    nodehead = insert(nodehead, 25);
    dlnode *lee = nodehead;
    eprintf("Head pointer points to score %i.\n", nodehead->n);
    
    nodehead = insert(nodehead, 35);
    dlnode *mark = nodehead;
    eprintf("Head pointer points to score %i.\n", nodehead->n);
    
    nodehead = insert(nodehead, 100);
    dlnode *james = nodehead;
    eprintf("Head pointer points to score %i.\n", nodehead->n);
    
    nodehead = insert(nodehead, 80);
    dlnode *sam = nodehead;
    eprintf("Head pointer points to score %i.\n", nodehead->n);
    
    eprintf("Zhiwei's score is %i.\n", zhiwei->n);
    eprintf("Lee's score is %i.\n", lee->n);
    eprintf("Mark's score is %i.\n", mark->n);
    eprintf("James's score is %i.\n", james->n);
    eprintf("Sam's score is %i.\n", sam->n);
    
    eprintf("50 exists? %i\n", search(nodehead, 80));
    
    // delete(james);
    
    // eprintf("100 exists? %i\n", search(nodehead, 100));
    
    // delete(zhiwei);
    // eprintf("%i %i %i %i %i\n", search(nodehead, 50), search(nodehead, 25), search(nodehead, 35), search(nodehead, 100), search(nodehead, 80));
    
    // delete(mark);
    // delete(lee);
    // delete(sam);
    
    destroy(nodehead);
    eprintf("%i %i %i %i %i\n", search(nodehead, 50), search(nodehead, 25), search(nodehead, 35), search(nodehead, 100), search(nodehead, 80));
    
    
}

dlnode *create(int n)
{
    // mallocate a new node
    dlnode *new = malloc(sizeof(dlnode));
    
    // check if the new node exists
    if (new == NULL)
    {
        exit(1);
    }
    
    // insert n in the new node
    new->n = n;
    
    // set the new node's prev & next pointers to NULL
    new->prev = NULL;
    new->next = NULL;
    
    // return the pointer to the new node
    return new;
}

dlnode *insert(dlnode* head, int n)
{
    // mallocate a new node
    dlnode *new = malloc(sizeof(dlnode));
    
    // check if the new node exists
    if (new == NULL)
    {
        exit(1);
    }
    
    // insert n in the new node
    new->n = n;
    
    // map the new node's prev pointer to NULL
    new->prev = NULL;
    
    // map the new node's next pointer to original head node
    new->next = head;
    
    // map the original head node's prev pointer to the new node
    head->prev = new;
    
    // return the pointer to the new node
    return new;
}

bool search(dlnode *head, int n)
{
    // create a traversal pointer
    dlnode *temp = head;
    
    // iterate through nodes
    while (temp != NULL)
    {
        if (temp->n == n)
        {
            return 1;
        }
        else
        {
            temp = temp->next;
        }
    }
    
    return 0;
}

void delete(dlnode *target)
{
    // create a traversal pointer
    dlnode *temp = target; 
    
    // check if temp exists
    if (target == NULL)
    {
        exit(1);
    }
    
    // re-map previous node's next pointer and/or next node's prev pointer
    if (target->prev !=NULL && target->next != NULL)
    {
        temp = target->prev;
        temp->next = target->next;
        
        temp = target->next;
        temp->prev = target->prev;
    }
    else if (target->prev != NULL && target->next == NULL)
    {
        temp = target->prev;
        temp->next = NULL;
    }
    else
    {
        eprintf("unable to delete head node\n");
        return;
    }
    
    free(target);
}

void destroy(dlnode *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        destroy(head->next);
        free(head);
    }
}