#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_MAX 26

typedef struct _hash
{
    char name[20];
    struct _hash *next;
}
hashline;

unsigned int hash(char *name);
hashline *insert(hashline *hash, char *name);
void display(hashline *hash);

int main(void)
{
    hashline *hashtable[HASH_MAX];
    
    // initiailise hashtable
    for (int i = 0; i < HASH_MAX; i++)
    {
        hashtable[i] = NULL;
    }
    
    // get user input and hash it
    fprintf(stdout, "enter the names to hash. enter any number to stop.\n");
    // iterate till the user enters an numeric value
    while (1)
    {
        char *name = get_string();
        int h = hash(name);
        if (h == 88)
        {
            fprintf(stdout, "Stopping the inputs.\n");
            break;
        }
        
        hashtable[h] = insert(hashtable[h], name);
    }
    
    for (int i = 0; i < HASH_MAX; i++)
    {
        fprintf(stdout, "Displaying values in hashtable[%i]...\n", i);
        display(hashtable[i]);
    }
}

unsigned int hash(char *name)
{
    if (name[0] >= 65 && name[0] <= 90)
    {
        return name[0]-65;
    }
    else if (name[0] >= 97 && name[0] <= 122)
    {
        return name[0]-97;
    }
    else
    {
        return 88;
    }
}

hashline *insert(hashline *hash, char *name)
{
    hashline *new = malloc(sizeof(hashline));
    
    strcpy(new->name, name);

    new->next = hash;
    
    return new;
}

void display(hashline *hash)
{
    hashline *trav = hash;
    
    if (trav == NULL)
    {
        fprintf(stdout, "The hashtable is empty.\n");
        return;
    }
    
    while (trav != NULL)
    {
        fprintf(stdout, "%s\n", trav->name);
        
        trav = trav->next;
    }
}