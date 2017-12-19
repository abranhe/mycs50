#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

long long exponent(int base, int power);
char upper(char c);
unsigned int nthfromright(unsigned long long digits, unsigned int nth);
int even(int number);
int digits(long long number);

int main(void)
{
    printf("test1 %lld\n", exponent(4,4));
    printf("test2 %c\n", upper('b'));
    printf("test3 %i\n", nthfromright(21285726845, 3));
    printf("test4 %i\n", even(100));
    printf("test5 %i\n", digits(23924324924284));
    
}

// calculate the value given the base and power of an exponent
long long exponent(int base, int power)
{
    long long x = 1;
    for (int i = 0; i < power; i++)
    {
        x *= base;
    }
    return x;
}

// return uppercase of a given character
char upper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 32;
    }
    else
    {
        return c;
    }
}


// return n'th digit starting from right
unsigned int nthfromright(unsigned long long digits, unsigned int nth)
{
    while (nth > 1)
    {
        digits /= 10;
        nth--;
    }
    
    return digits % 10;
}

// return true if a given number is even else return false
int even(int number)
{
    if (number % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// count the number of digits in a given number
int digits(long long number)
{
    int count = 0;
    long long divide = 1;
    
    while (number / divide > 1)
    {
        count += 1;
        divide *= 10;
    }
    
    return count;
}