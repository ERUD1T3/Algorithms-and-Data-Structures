/*****************************************
 * skipList.h 
 * Interface of skiplist
 ****************************************/

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PLUS_INF NULL
#define MINUS_INF NULL
#define SIZE 32

typedef unsigned int uint;
typedef struct entry Entry;
typedef struct skip_node SNode;
typedef struct skip_list SList;

struct entry {
    uint time;
    char activity[SIZE];
};

struct skip_node {
    Entry* log;
    SNode *prev, *next, *below, *above;
};


struct skip_list {
    uint size, level;
    SNode *head, *tail, *floor, *ceiling;
};


/*************************************************
 * METHODS PROTOTYPES
 ***********************************************/

Entry* get(uint key); // if key exists, return value associated with key; otherwise, return NULL
Entry* put(uint key, char* value); // if key doesn’t exist, add entry and return NULL; otherwise, replace value and return the old value
Entry* remove(uint key); // if key exists, remove entry and return its value; otherwise, return NULL
Entry* ceilingEntry(uint key); // return the entry with the smallest key greater than or equal to key; return NULL if no such entry exists
Entry* floorEntry(uint key); // return the entry with the largest key less than or equal to key; return NULL if no such entry exists
Entry* subMap(uint key1, uint key2); // return all entries with key such that key1 ≤ key ≤ key2

SNode* initEntry(uint time, char* activity);
SNode* initEntry(uint time, char* activity, SNode* prev, SNode* next, SNode* below, SNode* above);






#endif // SKIPLIST_H