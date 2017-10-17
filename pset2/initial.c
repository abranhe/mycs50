#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //get user input
    string s = get_string();

    //print first digit if it isn't an space
    if(s[0] != (' '))
    {
        printf("%c", toupper(s[0]));
    }

    //print the character after an space
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] != ' ' && s[i - 1] == ' ')
        {
            printf("%c", toupper(s[i]));
        }
    }
    printf("\n");
}
