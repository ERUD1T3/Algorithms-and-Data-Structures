/************************************
 * GRAPH INTERFACE FOR HW6
 * Josias Moukpe
 ************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"

#ifndef GRAPH_H
#define GRAPH_H 

typedef unsigned int uint;
typedef struct gnode GNode; 
typedef struct graph Graph; 


struct gnode 
{
    void* data;
    SLList* adj_node;
};

struct graph
{
    uint size;
    SLList* vertices;
    // SLList* edges;  
};


/********************************
 * PROTOTYPE METHODS
 *******************************/


GNode* initGNode(void) {
    // GNode*
}



/********************************
 * METHODS IMPLEMENTATION
 *******************************/ 

#endif // GRAPH_H