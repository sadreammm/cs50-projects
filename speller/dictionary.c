// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int wordCount=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *cursor = table[index];
    while(cursor!=NULL){
        if(strcasecmp(cursor->word,word)==0){
            return true;
        }
        cursor=cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word);
    int sum=0;
    for(int i=0; i<length; i++){
        sum+=tolower(word[i]);
    }
    return sum%N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for(int i=0;i<N;i++){
        table[i]=NULL;
    }

    FILE *file = fopen(dictionary,"r");
    if(file==NULL){
        fclose(file);
        return false;
    }

    char word[LENGTH + 1];
    while(fscanf(file,"%s",word)!=EOF){
        node *n = malloc(sizeof(node));
        if(n==NULL){
            return false;
        }
        strcpy(n->word,word);
        n->next = NULL;

        unsigned int index = hash(word);
        n->next = table[index];
        table[index] = n;

        wordCount++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i=0;i<N;i++){
        node *cursor = table[i];
        while(cursor!=NULL){
            node *tmp = cursor;
            cursor=cursor->next;
            free(tmp);
        }
    }
    return true;
}
