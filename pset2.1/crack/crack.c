#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // char string_a[4] = {'f', 'e', 'a', 'r'};
    // printf("%s\n", string_a);
    
    char alpha[52];
    // put in a to z in alpha elements 0 to 25
    for (int i = 0; i < 26; i++)
    {
        alpha[i] = (char) i + 97;
    }
    // put in A to Z in alpha elements 26 to 51
    for (int i = 26; i < 52; i++)
    {
        alpha[i] = (char) i + 65 - 26;
    }
    
    // test crypt()
    // printf("testing encryption%s\n", crypt("b", "50"));
    
    char pass[5];
    
    // brute force single character password
    pass[1] = '\0';
    for (int i = 0; i < 52; i++)
    {
        pass[0] = alpha[i];
        
        int cmp = strcmp(crypt(pass, "50"), argv[1]);
        if (cmp == 0)
        {
            printf("%s\n", pass);
            return 0;
        }
    }
    
    // brute force double character password
    pass[2] = '\0';
    for (int i = 0; i < 52; i++)
    {
        pass[0] = alpha[i];
        
        for (int j = 0; j < 52; j++)
        {
            pass[1] = alpha[j];
            
            int cmp = strcmp(crypt(pass, "50"), argv[1]);
            if (cmp == 0)
            {
                printf("%s\n", pass);
                return 0;
            }   
        }
    }
    
    // brute force triple character password
    pass[3] = '\0';
    for (int i = 0; i < 52; i++)
    {
        pass[0] = alpha[i];
        
        for (int j = 0; j < 52; j++)
        {
            pass[1] = alpha[j];
            
            for (int k = 0; k < 52; k++)
            {
                pass[2] = alpha[k];
                
                int cmp = strcmp(crypt(pass, "50"), argv[1]);
                if (cmp == 0)
                {
                    printf("%s\n", pass);
                    return 0;
                }   
            }
        }
    }
    
    // brute force quad character password
    pass[4] = '\0';
    for (int i = 0; i < 52; i++)
    {
        pass[0] = alpha[i];
        
        for (int j = 0; j < 52; j++)
        {
            pass[1] = alpha[j];
            
            for (int k = 0; k < 52; k++)
            {
                pass[2] = alpha[k];
                
                for (int l = 0; l < 52; l++)
                {
                    pass[3] = alpha[l];
                    
                    int cmp = strcmp(crypt(pass, "50"), argv[1]);
                    if (cmp == 0)
                    {
                        printf("%s\n", pass);
                        return 0;
                    }   
                }
            }
        }
    }
    
    // for (int i = 0; i < 52; i++)
    // {
    //     pass[0] = alpha[i];
    //     for (int j = 0; j < 52; i++)
    //     {
    //         pass[1] = alpha[j];
    //         for (int k = 0; k < 52; k++)
    //         {
    //             pass[2] = alpha[k];
    //             for (int l = 0; l < 52; l++)
    //             {
    //                 pass[3] = alpha[l];
    //             }
    //         }
    //     }
    // }
    
    // printf("%s\n", pass);
    
    printf("Error: Unable to find the password\n");
    return 1;
}