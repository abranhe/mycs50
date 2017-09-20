/*
*
*   Mario.c print a pyrimid
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
#include <cs50.h>

int main(void) 
{
	int height = 0, z;
	
	//get user input
	do
	{
        printf("Enter a non-negative integer < 24:");
		height = get_int();
        
        if (height == 0)
        {
            return 0;
        }
	}
	while (height < 1 || height > 23);

	for(int x = 0; x < height; x++) 
	{
        for(int y = 0; y < height-x-1; y++)
        {
            printf("%s", " ");
        }
        
        for(z = 0; z < x+1; z++)
		{
			printf("#"); //print left #s
		}
        printf("  ");
        
        for(z = 0; z < x+1; z++)
		{
			printf("#"); //print right #s
		}
        
		printf("\n");
        	
	}	
	return 0;
}
