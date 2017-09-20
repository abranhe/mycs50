/*
*
*   greedy.c Implement a program that calculates the minimum
*   number of coins required to give a user change.
*   
*   Author: Carlos Abraham Hernandez, www.19cah.com
*	
*  	 twitter.com/19cah    github.com/19cah
*  	 facebook.com/19cah   stackoverflow.com/story/19cah
*	 instagram.com/19cah  linkedin.com/in/19cah
*	 bitbucket.org/19cah  repl.it/@19cah
*
*/
#include <stdio.h>
#include <math.h>  // to use round()
#include <cs50.h> //include cs50 library

int main(void)
{
    //Get user input
    float change;
	do
	{
        printf("O hai! How much change is owed?\n");
        change = get_float();
	}
	while (change < 0);
	
	int total, no_coins = 0;
	
	//Change from $ to ¢
	change = change * 100.0;
	
	total = (int) round(change);
	
	//When use Quarters
	while (total >=25)
	{
	    no_coins++;
	    total = total - 25;
	}
	
	//When use Dimes
	while (total >=10)
	{
	    no_coins++;
	    total = total - 10;
	}
	
	//When use Nickels
	while (total >= 5)
	{
	    no_coins++;
	    total = total - 5;
	}
	
	//When use Pennies
	while (total >= 1)
	{
	    no_coins++;
	    total = total - 1;
	}
	
    printf("%d\n", no_coins);
}
