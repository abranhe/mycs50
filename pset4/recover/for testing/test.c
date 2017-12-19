#include <stdio.h>
#include <stdint.h>

int main(void)
{
    
    FILE *readfile = fopen("testtext.txt", "r");
    if (readfile == NULL)
    {
        return 1;
    }
    
    FILE *writefile = fopen("haha.txt", "w");
    if (writefile == NULL)
    {
        fclose(readfile);
        return 1;
    }

    int checkeof;
    char *array[200];
    
    while (1)
    {
        checkeof = fread(array, 1, 200, readfile);
        
        fwrite(array, 1, checkeof, writefile);
        if (checkeof != 200)
        {
            fprintf(stdout, "ended\n");
            break;
        }
    }
    
}