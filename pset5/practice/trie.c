// warning this is not fixed. malloc pointers are not initialised***

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _trie
{
    char university[20];
    struct _trie *paths[10];
}
trie;

bool load(trie *root, char *filename);
bool insert(trie *root, int year, char *university);
void display(trie *root);
void destroy(trie *root);
unsigned int nthfromright(unsigned int digits, unsigned int nth);


int main(void)
{
    // create a root trie
    trie *root = malloc(sizeof(trie));
    
    // load trielist.txt
    load(root, "trielist.txt");
    
    // display trie
    display(root);
    
    // destroy trie
    destroy(root);
    
}

bool load(trie *root, char *filename)
// 4-digit year followed by a space and then university's name capped at 20 characters
{   
    eprintf("start loading the file.\n");
    
    FILE *loadfile = fopen(filename, "r");
    if (loadfile == NULL)
    {
        fprintf(stderr, "Could not open the file %s.\n", filename);
        return 1;
    }
    
    char year[5];
    year[4] = '\0';
    char university[20];
    
    while (1)
    {
        // read the 4-digit as year
        for (int i = 0; i < 4; i++)
        {
            fread(&year[i], 1, 1, loadfile);
        }
        
        // skip over the space
        fseek(loadfile, 1, SEEK_CUR);
        
        int index = 0;
        
        // read university
        while (1)
        {
            fread(&university[index], sizeof(char), 1, loadfile);
            
            // break once reach dot which represents end of the word in the textfile
            if (university[index] == '.')
            {
                university[index] = '\0';
                break;
            }
            
            index++;
        }
        
        insert(root, atoi(year), university); 
        
        // get CRLF instead of fseek to check feof
        fgetc(loadfile);
        // fseek(loadfile, 1, SEEK_CUR);
        
        // exit if reached end of file
        if (feof(loadfile))
        {
            break;
        }
    }

    fclose(loadfile);
    
    eprintf("finished loading the file.\n");
    return 0;
}

bool insert(trie *root, int year, char *university)
{
    eprintf("inserting year %i university %s\n", year, university);

    trie *trav = root;
    
    // navigating from root to the leaf
    for (int i = 0; i < 4; i++)
    {
        int y = nthfromright(year, 4-i);
        
        if (trav->paths[y] == NULL)
        {
            trie *new = malloc(sizeof(trie));
            trav->paths[y] = new;
            trav = new;
        }
        else
        {
            trav = trav->paths[y];
        }
    }
    
    strcpy(trav->university, university);
    
    return 0;
}

void display(trie *root)
{
    trie *trav = root;
    trie *trav1;
    trie *trav2;
    trie *trav3;
    trie *trav4;
    
    for (int i = 0; i < 10; i++)
    {
        if (trav->paths[i] != NULL)
        {
            trav1 = trav->paths[i];
            
            for (int j = 0; j < 10; j++)
            {
                if (trav1->paths[j] != NULL)
                {
                    trav2 = trav1->paths[j];
                    
                    for (int k = 0; k < 10; k++)
                    {
                        if (trav2->paths[k] != NULL)
                        {
                            trav3 = trav2->paths[k];
                            
                            for (int l = 0; l < 10; l++)
                            {
                                if (trav3->paths[l] != NULL)
                                {
                                    trav4 = trav3->paths[l];
                                    
                                    fprintf(stdout, "year %i%i%i%i. university %s.\n", i, j, k, l, trav4->university);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void destroy(trie *root)
{
    trie *trav = root;
    trie *trav1;
    trie *trav2;
    trie *trav3;
    trie *trav4;
    
    for (int i = 0; i < 10; i++)
    {
        if (trav->paths[i] != NULL)
        {
            trav1 = trav->paths[i];
            
            for (int j = 0; j < 10; j++)
            {
                if (trav1->paths[j] != NULL)
                {
                    trav2 = trav1->paths[j];
                    
                    for (int k = 0; k < 10; k++)
                    {
                        if (trav2->paths[k] != NULL)
                        {
                            trav3 = trav2->paths[k];
                            
                            for (int l = 0; l < 10; l++)
                            {
                                if (trav3->paths[l] != NULL)
                                {
                                    trav4 = trav3->paths[l];
                                    
                                    free(trav4);
                                }
                            }
                            
                            free(trav3);
                        }
                    }
                    
                    free(trav2);
                }
            }
            
            free(trav1);
        }
    }
    
    free(root);
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