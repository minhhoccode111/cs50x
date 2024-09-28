// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// maybe this cause slower
const unsigned int N = 104729;

// Hash table, an array of pointers
node *table[N];

unsigned int countWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // first hash the string to find the bucket that string belong to
    // while not reach the end of the bucket, find the word
    int hashed = hash(word);
    node *list = table[hashed];
    while (list != NULL)
    {

        // compare 2 lower case words
        // if (strcmp(list->word, lowerWord) == 0)
        if (strcasecmp(list->word, word) == 0)
        {
            return true;
        }

        // else move pointer to next node in the bucket
        list = list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    // Process each character in the word
    while ((c = *word++))
    {
        // Convert the char to lowercase to ensure case-insensitive hashing
        c = tolower(c);

        // hash = hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    // Return the computed hash value modulo the number of buckets
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // read the dictionary file
    FILE *dict = fopen(dictionary, "r"); 

    // make sure dict is opened
    if (dict == NULL)
    {
        return false;
    }

    // an array of char to hold words
    char word[LENGTH + 1];

    // to hold char read from dict file
    char charHolder;

    // to identify position to copy char from dict file
    int index = 0;

    // while there is something to read from the file
    while (fread(&charHolder, sizeof(char), 1, dict))
    {
        // current char is new line, mean the end of word
        if (charHolder == '\n')
        {
            // terminate the word
            word[index] = '\0';

            // hash the word to get a number
            int hashed = hash(word);

            // create a node of current word to store in hashed bucket
            node *current = malloc(sizeof(node));

            // make sure it is usable
            if (current == NULL)
            {
                fclose(dict);
                return false;
            }

            // copy word to current node.word
            strcpy(current->word, word);

            // which ever address table[hashed] is holding will be current.next
            current->next = table[hashed];

            // and make table[hashed] to hold current node
            table[hashed] = current;

            // increase words in dict, after adding a word
            countWords++;

            // prepare for new word
            index = 0;
        }
        // else not new line 
        else
        {
            // then add that char to word array
            word[index] = charHolder;

            // increase index
            index++;
        }
    }

    // close the file since dict already loaded into memory
    fclose(dict);

    // return success flag
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return countWords;
}

// free the table recursion
void freeList(node *list)
{
    if (list == NULL) 
        return;
    freeList(list->next);
    free(list);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    countWords = 0;
    for (int i = 0; i < N; i++)
    {
        freeList(table[i]);
        table[i] = NULL;
    }
    return true;
}
