#include <stdio.h>
#include <cs50.h> //include cs50 library to use "get_long_long();"

int main(void)
{
    long long  cc_number;

    //get user input
    printf("number: ");
    cc_number = get_long_long();

    //measure the credit card length
    int count = 0;
    long long cc_length = cc_number;
    while (cc_length != 0)
    {
        cc_length /= 10;
        count++;
    }

    if((count == 13) || (count == 15) || (count == 16))
    {
        int digit[count];

        for (int i = 0; i < count; i++)
        {
            digit[i] = cc_number % 10;
            cc_number = cc_number / 10;
        }
        int originaldigit[count];

        for (int i = 1; i < count; i++)
        {
            originaldigit[i] = digit[i];
        }

        for (int i = 1; i < count; i+=2)
        {
            digit[i] = digit[i] * 2;
        }

        int totalSum = 0;
        int sum;

        for (int i = 0; i < count; i++)
        {
            sum = (digit[i] % 10) + (digit[i]/10 % 10);
            totalSum = totalSum + sum;
        }

        //check if the last digit of the sum is 0
        int zero = totalSum % 10;
        if(zero == 0)
        {
            if(count == 16)
            {
                if (originaldigit[15] == 4)
                {
                    printf("VISA\n");
                }
                else if (originaldigit[15] == 5 && (originaldigit[14] == 1 || originaldigit[14] == 2 || originaldigit[14] == 3 || originaldigit[14] == 4 || originaldigit[14] == 5))
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }

            if(count == 15)
            {
                if (originaldigit[14] == 3 && (originaldigit[13] == 4 || originaldigit[13] == 7))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            if (count == 13)
            {
                if (originaldigit[12] == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
