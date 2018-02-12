/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

//construct a node defintion to use to hold words in your hash table
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

// define a dictionary hashtable
#define HASHSIZE 210912 // 26 * 26 * 26 *12= 210912 using the first 4 characters

//declaration of an array of nodes called hash the size of the HASHSIZE(210912)
node* hash[HASHSIZE] = {NULL}; 
//converts a char to a value between 0 and 25. checks that value against a counter in a 
//for loop with a nested if statement storing whatever i is when equal to x inside hash and returning hash
int selector(char c)
{
    unsigned int hash = 0;
    int x = (int)c-97;
    for(int i = 0; i < 28; i++)
    {
        if(x==i)
        {
            hash = i;
        }         
    }
    return hash;
}
    
/**
 * Calculater for the hash index
 */
int hasher(char* word)
{
    unsigned long hash, hash1, hash2=0, hash3 = 0, hash4 = 0;
    hash1 = selector(word[0]);
    if (word[1] == '\0')
    {
        hash2 = 0;
        hash3 = 0; 
        hash4 = 0;   
    }
    else if (word[1] != '\0' && word[2] == '\0')
    {
        hash2 = selector(word[1]);
        hash3 = 0;  
        hash4 = 0;  
    }
    else if (word[1] != '\0' && word[2] != '\0' && word[3] == '\0') 
    {
        hash2 = selector(word[1]);
        hash3 = selector(word[2]);
        hash4 = 0;
    }     
    else
    {
        hash2 = selector(word[1]);
        hash3 = selector(word[2]);
        hash4 = selector(word[3]);
    } 
    hash = (hash1*26)+(hash2*26)+(hash3*26)+(hash4*12);
    return hash;
}  


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // copy the uppercased argument for comparison
    char copy[LENGTH + 1];
    int n = strlen(word);   
    for(int i = 0; i < n; i++)
    {
        copy[i] = tolower(word[i]);
    }
    copy[n] = '\0';    
    // find the correct hash index for word loop
    int index = hasher(copy);   
    if (hash[index] == NULL)
    {
        return false;
    }
    else
    {
        node* tmp = hash[index];
    
        while (tmp->next != NULL)
        {
            if (strcmp(copy, tmp->word) == 0)
            {
                return true;
            }
            tmp = tmp->next;
        }
        
        if (strcmp(copy, tmp->word) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{ 
    // open dictionary to the RAM
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // load words from dictionary
    char buffer[LENGTH + 2];
    
    while (fgets(buffer, LENGTH + 2, file))
    {
        // overwrite the \n with \0
        buffer[strlen(buffer) - 1] = '\0';
        
        // lowercase for word
        for (int i = 0, n = strlen(buffer); i < n; i++)
        {
            buffer[i] = tolower(buffer[i]);
        }

        // copy word into temp node
        node* temp = malloc(sizeof(node));
        strncpy(temp->word, buffer, LENGTH + 1);
        temp->next = NULL;
        
        // update the node into the correct place
        int index = hasher(buffer);
        
        if (hash[index] == NULL)
        {
            hash[index] = temp;
        }
        else
        {
            // loop through the linked list and insert it into the table
            node* tmp = hash[index];
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            // assign the node to the last of the linked list
            tmp->next = temp;
        }
    }

    // close the file
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // initialize dictionary's size
    unsigned int size = 0;
    
    for (int i = 0; i < HASHSIZE; i++)
    {
        if (hash[i] != NULL)
        {
            size++;
            for(node* tmp = hash[i]; tmp->next != NULL; tmp = tmp->next)
                size++;
        }
    }
    return size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // loop through the hash and free each linked list
    for (int i = 0; i < HASHSIZE; i++)
    {
        node* first = hash[i];
        while (first != NULL)
        {
            node* next = first->next;
            free(first);
            first = next;
        }
    } 
    return true;
}
