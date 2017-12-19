#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int error();

int main(int argc, string argv[])
{
    // exit if argument is not entered or has more than 1
    if (argc != 2)
    {
        return error();
    }
    
    // exit if non-alpha char in argument
    for (int i = 0, n = strlen(argv[1]); i<n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            return error();
        }
    }
    
    int key = 0;
    int ctext = 0;
    int keylen = strlen(argv[1]);
    
    printf("plaintext:  ");
    string ptext = get_string();
    if (ptext == NULL)
    {
        return 1;
    }
    printf("ciphertext: ");
    
    // iterate the characters in the plain text
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (isalpha(ptext[i]))
        {
            int zwrap = (islower(ptext[i])) ? (int) 'z' : (int) 'Z';
        
            ctext = (int) ptext[i] + toupper(argv[1][key]) - 65;
            int ctextwrap = (ctext > zwrap) ? ctext - 26 : ctext;
            printf("%c", ctextwrap);
            key = (key + 1) % keylen;
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
    return 0;
}

int error()
{
    printf("Usage: ./ vigenere TEXT\n");
    return 1;
}