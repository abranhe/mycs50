#include <cs50.h>
#include <ctype.h>
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
    
    printf("plaintext:  ");
    string ptext = get_string();
    if (ptext == NULL)
    {
        return 1;
    }
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (isalpha(ptext[i]))
        {
            int norm = (islower(ptext[i])) ? 97 : 65; 
            printf("%c", (ptext[i] - norm + atoi(argv[1])) % 26 + norm);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
    return 0;
}