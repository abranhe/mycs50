/*
*
*  	Water.c takes an input in minutes: How long have you been taking a shower?
*   and output how many bottles of water did you use
*   
*   Author: Carlos Abraham Hernandez, www.19cah.ml
*	
*  	 twitter.com/19cah    github.com/19cah
*  	 facebook.com/19cah	 stackoverflow.com/story/19cah
*	   instagram.com/19cah	 linkedin.com/in/19cah
*	   bitbucket.org/19cah   repl.it/@19cah
*
*/

#include <stdio.h>
#include <cs50.h> //include cs50 library

int main(void)
{
    int minutes, bottles;
    
    do
    {
        printf("minutes: \n");
        minutes = get_int();
    }
    while(minutes < 1);
    
    bottles = (minutes * 12);
    printf("bottles: %d\n", bottles);
}
