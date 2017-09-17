/*
*
*   Mario.c print a half of a pyrimid
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
	int height = 0;

	//get user input
	do
	{
        printf("Height: ");
		height = get_int();

        if (height == 0)
        {
            return 0;
        }
	}
	while (height < 1 || height > 23);

	for(int i = 0; i < height; i++)
	{
        for(int j = 0; j < (height - i - 1); j++)
        {
            printf("%s", " ");
        }

		for(int k = 0; k <= (i + 1); k++)
		{
			printf("#"); //print #
		}
		printf("\n");
	}
	return 0;
}
