#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error. Please enter nonnegative integer as an argument.\n");
        return 1;
    }
    
    int key = atoi(argv[1]) % 26;
    int ctext = 0;
    
    printf("plaintext:  ");
    string ptext = get_string();
    if (ptext == NULL)
    {
        return 1;
    }
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (ptext[i] >= 'a' && ptext[i] <= 'z')  // or <ctype.h> islower(ptext[i])
        {
            ctext = (int) ptext[i] + key;
            int ctextwrap = (ctext > 'z') ? ctext - 26 : ctext;
            printf("%c", ctextwrap);
        }
        else if (ptext[i] >= 'A' && ptext[i] <= 'Z')  // or <ctype.h> isupper(ptext[i])
        {
            ctext = (int) ptext[i] + key;
            int ctextwrap = (ctext > 'Z') ? ctext - 26 : ctext;
            printf("%c", ctextwrap);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
    return 0;
}