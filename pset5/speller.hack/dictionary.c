/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// initiailise hash
hash *hashtable[HASHTABLE_SIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    char wordtohash[LENGTH+1];
    int i = 0;
    
    // set word to lower-case to make it case-insensitive
    while (word[i] != '\0')
    {
        wordtohash[i] = (isalpha(word[i])) ? tolower(word[i]) : word[i];
        i++;
    }
    wordtohash[i] = '\0';
    
    unsigned int hashnum = hash_it(wordtohash);
    hash *trav = hashtable[hashnum];
    
    while (trav != NULL)
    {
        if (strcmp(trav->word, wordtohash) == 0)
        {
            return true;
        }
        else
        {
            trav = trav->next;
        }
    }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // initiailse hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    
    // open the dictionary file for loading
    FILE *df = fopen(dictionary, "r");
    
    // prepare to load the words
    char word[LENGTH+1];
    unsigned int hashnum = 0;
    
    // loading the dictionary via fscanf
    while (fscanf(df, "%s", word) == 1)
    {
            // hash word
            hashnum = hash_it(word);
            
            // store word in hashtable
            hash *new = malloc(sizeof(hash));
            strcpy(new->word, word);
            new->next = hashtable[hashnum];
            hashtable[hashnum] = new;
    }
    
    fclose(df);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // initialise count number
    unsigned int ct = 0;
    hash *trav;
    
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        trav = hashtable[i];
        
        while (trav != NULL)
        {
            ct++;
            trav = trav->next;
        }
    }
    
    return ct;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    hash *trav;
    hash *travnext;
    
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        trav = hashtable[i];
        
        while (trav != NULL)
        {
            travnext = trav->next;
            free(trav);
            trav = travnext;
        }
    }
    
    return true;
}

// credit: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}