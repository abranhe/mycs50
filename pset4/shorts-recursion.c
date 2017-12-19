#include <cs50.h>
#include <stdio.h>

int collatz(int n);
int collatz_alt(int n, int c);

int main(void)
{
    int n;
    do
    {
        printf("Enter a positive integer: ");
        n = get_int();
    }
    while (n <= 0);
    
    int c = collatz(n);
    printf("Number of times to get to 1: %i\n", c);
}

int collatz(int n)
{
    //base case
    if (n==1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n/2);
    else
        return 1 + collatz(3*n + 1);
}

int collatz_alt(int n, int c)
{
    //base case
    if (n == 1)
        return c;
    //recursive case 1
    else if (n % 2 == 0)
        return collatz_alt(n/2, c+1);
    // recursive case 2
    else if (n % 2 == 1)
        return collatz_alt(3*n + 1, c+1);
    else
        return 0;
}