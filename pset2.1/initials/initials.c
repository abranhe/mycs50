#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // set 0 if current char is a space, else 1
    int counter = 0;
    
    string s = get_string();
    if (s != NULL)
    {
        // iterate i'th char of the string
        for (int i = 0; i < strlen(s); i++)
        {
            // if the current char is not a space and the preceding char is a space
            if (s[i] != ' ' && counter == 0)
            {
                printf("%c",toupper(s[i]));
                counter = 1;
            }
            // if the current char is a space
            else if (s[i] == ' ')
            {
                counter = 0;
            }
        }
        printf("\n");
    }
    
}