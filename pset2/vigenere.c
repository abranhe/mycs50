#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if it has correct usage of argc
    if(argc != 2)
    {
        printf("Usage: %s k\n", argv[0]);
        return 1;
    }
    
    string key = argv[1];
    //value of lenght of the key
    int lengthKey = strlen(key);
    
    //check if the Key have a valid value 
    for(int i = 0; i < lengthKey; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        }
    }
    
    //get user input
    printf("plaintext: ");
    string s = get_string();
    printf("ciphertext: ");
    
    for(int i = 0, j = 0, plainTLenght = strlen(s); i < plainTLenght; i++, j++)
    {
        if(i >= lengthKey)
            i = 0;
        
        //convert key to shift
        int alphaNum = key[i];
        
        //if key is uppercase
        if(isupper(alphaNum))
            alphaNum -= 'A';
        
        //if key is lowercase
        if(islower(alphaNum))
            alphaNum -= 'a';
        
        int value = s[j]; //ASCII value
        
        //skip any non-alphabetical character
        if(!isalpha(value))
        {
            i--;
        }
        
        //uppercase
        if(isupper(value))
        {
            //change from ASCII value to Alphabetical Index
            printf("%c", ((((value - 65) + alphaNum) % 26) + 65));
        }
        //lowercase
        else if(islower(value))
        {
            //change from ASCII value to Alphabetical Index
            printf("%c", ((((value - 97) + alphaNum) % 26) + 97));
        }
        //print any non alphabetic character
        else//(!isalpha(s[j]))
        {
            printf("%c", s[j]);
        }
        
        if(j > (plainTLenght - 2))
            break;
    }
    printf("\n");
    return 0;
}
