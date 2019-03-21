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
    Entry log;
    struct skip_node *prev, *next, *below, *above;
};


struct skip_list
{
    uint size;
    struct skip_node* head;
};









#endif // SKIPLIST_H