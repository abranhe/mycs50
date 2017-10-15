#include <stdio.h>
#include <cs50.h>
#include <stdlib.h> //to use atoi
#include <string.h> //to use strlen
#include <ctype.h> //to use isupper, islower & isalpha

int main(int argc, string argv[])
{
    //check if it has correct usage of argc
    if(argc != 2)
    {
        printf("Usage: %s k\n", argv[0]);
        return 1;
    }
    //convert string to int
    int Key = atoi(argv[1]);

    //get user input
    printf("plaintext: ");
    string s = get_string();

    printf("ciphertext: ");

    for(int i = 0, n = strlen(s); i < n; i++)
    {
        int value = s[i]; //ASCII value

        //print any non alphabetic character
        if(!isalpha(s[i]))
        {
            printf("%c", s[i]);
        }
        //uppercase
        else if(isupper(s[i]))
        {
            //change from ASCII value to Alphabetical Index
            printf("%c", ((((value - 65) + Key) % 26) + 65));
        }
        //lowercase
        else if(islower(s[i]))
        {
            //change from ASCII value to Alphabetical Index
            printf("%c", ((((value - 97) + Key) % 26) + 97));
        }
    }
    printf("\n");

    return 0;
}
