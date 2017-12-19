#include <ctype.h>
#include <stdio.h>

unsigned int nthfromright(unsigned int digits, unsigned int nth);


int main(void)
{
    fprintf(stdout, "%i\n", nthfromright(1088, 4));
    fprintf(stdout, "%i\n", nthfromright(1088, 3));
    fprintf(stdout, "%i\n", nthfromright(1088, 2));
    fprintf(stdout, "%i\n", nthfromright(1088, 1));
    
    char c = 'c';
    int i = tolower(c) - 64;
    fprintf(stdout, "%i\n", i);
    
}

unsigned int nthfromright(unsigned int digits, unsigned int nth)
{
    while (nth > 1)
    {
        digits /= 10;
        nth--;
    }
    
    return digits % 10;
}