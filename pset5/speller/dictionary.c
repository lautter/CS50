// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// const unsigned int N = 1;
#define N 6000000
unsigned int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //variables declaration
    unsigned int hash_i = hash(word);
    node *cursor = table[hash_i];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number: addapted from the djb2 disponible on http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash = 3;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //buffer for fscanf
    char word[LENGTH + 1];

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    while ((fscanf(file, "%s", word) != EOF))
    {
	    unsigned int index = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
		{
		    return false;
		}

	    if (table[index] == NULL)
		{
    		strcpy(n->word, word);
    		n->next = NULL;
    		table[index] = n;
		}

        else
        {
    		strcpy(n->word, word);
    		n->next = table[index];
    		table[index] = n;
        }
        ++wordCount;
	}
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; ++i)
    {
        if (table[i] != NULL)
        {
            if (table[i]->next != NULL)
            {
                while (table[i]->next != NULL)
                {
                    node *tmp = table[i]->next;
                    free(table[i]);
                    table[i] = tmp;
                }
            }
            free(table[i]);
        }
    }

    return true;
}
