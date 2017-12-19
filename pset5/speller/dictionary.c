/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

// initialise root pointer
trie *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // check if root exists
    if (root == NULL)
    {
        fprintf(stderr, "Dictionary is not loaded.\n");
        return 0;
    }
    
    // prepare to iterate the word's characters
    trie *trav = root;
    int c = 0;
    int path = 0;
    
    while (word[c] != '\0')
    {
        // set path number, a to 1, z to 26, apostrophe to 0
        path = (isalpha(word[c])) ? (tolower(word[c]) - 96) : 0;
        
        // if path exists, go to next path else return false
        if (trav->paths[path] != NULL)
        {
            trav = trav->paths[path];
        }
        else
        {
            return false;
        }
        
        // next n'th of the word
        c++;
    }
    
    // check wordexists when reached end of word
    return trav->wordexists;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    root = malloc(sizeof(trie));
    
    // check if the root is created
    if (root == NULL)
    {
        fprintf(stderr, "Could not mallocate rootd.\n");
        return false;
    }
    
    // initialise root
    root->wordexists = NULL;
    for (int i = 0; i < PATHS; i++)
    {
        root->paths[i] = NULL;
    }
    
    // prepare to load the words
    char word[LENGTH+1];
    int index = 0;
    int loadct = 0;
    
    // open the dictionary file for loading
    FILE *df = fopen(dictionary, "r");
    
    // loading the dictionary
    for (int c = fgetc(df); c != EOF; c = fgetc(df))
    {
        // alphabets or apostrophe only
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;
        }
        // treat new line as end of word
        else if (c == '\n' && index > 0)
        {
            word[index] = '\0';
            // fprintf(stderr, "load(): loading %s\n", word); 
            
            // loading words into dictionary root
            if (loadword(root, word))
            {
                loadct++;
            }
            
            // initialise index for next word
            index = 0;
        }
        // reset index if c is not a-z, apostrophe or \n
        else
        {
            index = 0;
        }
    }
    
    fclose(df);
    
    // fprintf(stdout, "load(): Loaded %i words.", loadct);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (root == NULL)
    {
        fprintf(stderr, "Dictionary is not loaded.\n");
        return 0;
    }
    
    // fprintf(stdout, "size(): count: %u\n", count(root));
    return count(root);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if (root == NULL)
    {
        fprintf(stderr, "Dictionary is not loaded.\n");
        return false;
    }
    
    destroy(root);
    return true;
}


bool loadword(trie *root, char *word)
{
    // check root exists
    if (root == NULL)
    {
        fprintf(stderr, "loadword(): Could not find the root.\n");
        return false;
    }
    
    // create a traversal pointer
    trie *trav = root;
    int path = 0;
    int c = 0;
    
    // for (int c = 0; c != '\0' && c <= LENGTH; c++)
    while (word[c] != '\0' && c <= LENGTH)
    {
        // set path number, a to 1, z to 26
        if (isalpha(word[c]))
        {
            path = toupper(word[c]) - 64;
        }
        // set path number, apostrophe to 0
        else if (word[c] == '\'')
        {
            path = 0;
        }
        // abandon if found neither a-z or apostrophe
        else
        {
            fprintf(stderr, "loadword(): Found illegible character: %c\n", word[c]);
            return false;
        }
        
        // fprintf(stdout, "loadword(): c: %i, path number: %i\n", c, path);  // for testing: print char by char
        
        if (path >= 0 && path < PATHS)
        {
            // create path if NULL
            if (trav->paths[path] == NULL)
            {
                trie *new = malloc(sizeof(trie));
                for (int i = 0; i < PATHS; i++)
                {
                    new->paths[i] = NULL;
                }
                new->wordexists = false;
                trav->paths[path] = new;
            }
            
            // point trav to next path
            trav = trav->paths[path];
            
            // next c'th of the word
            c++;
        }
        // just a control check during testing
        else
        {
            fprintf(stderr, "loadword(): path number error: %i\n", path);
            return false;
        }
    }
    
    if (word[c] == '\0')
    {
        trav->wordexists = true;
        // fprintf(stdout, "loadword(): loaded %s.\n", word);
        return true;
    }
    else
    {
        // fprintf(stderr, "loadword(): could not load %s.", word);
        return false;
    }
}

unsigned int count(trie* current)
{
    // base
    if (current == NULL)
    {
        return 0;
    }
    // recursive
    else
    {
        int n = 0;
        
        if (current->wordexists)
        {
            n++;
        }
        
        for (int i = 0; i < PATHS; i++)
        {
            n = n + count(current->paths[i]);
        }
        
        return n;
    }
}

void destroy(trie *current)
{
    // base
    if (current == NULL)
    {
        return;
    }
    // recursive
    else
    {
        for (int i = 0; i < PATHS; i++)
        {
            destroy(current->paths[i]);
        }
        
        free (current);
        
        return;
    }
}
