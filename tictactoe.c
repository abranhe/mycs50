#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

void show(char array[3][3]); 
bool update(char array[3][3], char *coord, char a);
bool end(char array[3][3]);

int main(void)
{
    // create tic tac toe
    char tictactoe[3][3];
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            tictactoe[x][y] = ' ';
        }
    }
    
    // start a game
    show(tictactoe);
    
    // play the game
    bool update_res = false;
    
    // initialise for player1
    int player = 1;
    char playersymbol = '#';
    
    while (1)
    {
        while (1)
        {
            if (!update_res)
            {
                printf("Player %i: enter the coordinates e.g. a1\n", player);
            }
            char *coord = get_string();
            
            if (update(tictactoe, coord, playersymbol))
            {
                break;
            }
        }
        show(tictactoe);
        
        if (end(tictactoe))
        {
            return 0;
        }
        
        switch(player)
        {
            case 1:
                player = 2;
                playersymbol = '@';
                break;
            case 2:
                player = 1;
                playersymbol = '#';
                break;
        }
    }
    
    fprintf(stderr, "unknown error.\n");
    return 1;

}

void show(char array[3][3])
{
    printf("Tic Tac Toe\n");
    printf("  | a | b | c\n");
    for (int y = 0; y < 3; y++)
    {
        printf("--|---|---|--\n");
        printf("%i ", y+1);
        for (int x = 0; x < 3; x++)
        {
            printf("| %c ", array[x][y]);
        }
        printf("\n");
    }
}

bool update(char array[3][3], char *coord, char a)
{
    if (coord[2] != '\0')
    {
        fprintf(stderr, "Enter a1 to c3 only.\n");
        return false;
    }
    
    // set x coord
    int x = 0;
    
    if (tolower(coord[0]) >= 'a' && tolower(coord[0]) <= 'c')
    {
        x = tolower(coord[0]) - 97;
    }
    else
    {
        fprintf(stderr, "Enter a1 to c3 only.\n");
        return false;
    }
    
    // set y coord
    int y = 0;
    if (coord[1] == '1' || coord[1] == '2' || coord[1] == '3')
    {
        y = atoi(&coord[1]) - 1;
    }
    else
    {
        fprintf(stderr, "Enter a1 to c3 only.\n");
        return false;
    }
    
    // update tictactoe
    if (array[x][y] == ' ')
    {
        array[x][y] = a;
        return true;
    }
    else
    {
        fprintf(stderr, "The coordinate is already taken.\n");
        return false;
    }
}

bool end(char array[3][3])
{
    // test if the game is won
    for (int i = 0; i < 3; i++)
    {
        if (((array[i][0] == array[i][1]) && (array[i][1] == array[i][2] && array[i][2] != ' ')) ||
            ((array[0][i] == array[1][i]) && (array[1][i] == array[2][i] && array[2][i] != ' ')))
            {
                fprintf(stdout, "Game over!\n");
                return true;
            }
    }
    
    if ((((array[0][0] == array[1][1]) && (array[1][1] == array[2][2])) ||
        ((array[0][2] == array[1][1]) && (array[1][1] == array[2][0]))) && array[1][1] != ' ')
        {
            fprintf(stdout, "Game over!\n");
            return true;
        }
    
    
    // check if there's any blank space left
    int blank = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (array[i][j] == ' ')
            {
                blank++;
            }
        }
    }
    
    if (blank == 0)
    {
        fprintf(stdout, "It's a draw!\n");
        return true;
    }

        
    return false;
}