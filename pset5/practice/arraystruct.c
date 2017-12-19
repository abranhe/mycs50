#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int n;
    char name[10];
}
node;

int main(void)
{
    node test[5];
    
    for (int i = 0; i < 5; i++)
    {
        test[i].n = i*3;
        
        fprintf(stdout, "enter string.\n");
        char *user = get_string();
        
        strcpy(test[i].name, user);
    }
    
    fprintf(stdout, "printing result...\n");
    for (int i = 0; i < 5; i++)
    {
        fprintf(stdout, "no. %i: n is %i and name is %s\n", i, test[i].n, test[i].name);
    }
}