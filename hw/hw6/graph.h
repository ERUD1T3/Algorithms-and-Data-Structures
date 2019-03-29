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
typedef struct vertex Vertex; 
// typedef struct edge Edge;
typedef struct graph Graph; 


struct vertex 
{
    void* data;
    SLList* adj_node;
};

struct graph
{
    uint size;
    SLList* vertices;
    SLList* edges;  
};


/********************************
 * PROTOTYPE METHODS
 *******************************/

Vertex* initVertex(void* data);
Graph* initGraph();



/********************************
 * METHODS IMPLEMENTATION
 *******************************/ 


/* initialize a new graph node with data param and an empty list of adjacent nodes */
Vertex* initVertex(void* data) {
    Vertex* new_node = (Vertex*)malloc(sizeof(Vertex));
    new_node->data = data;
    new_node->adj_node = initList(); 
    return new_node;
}


/* initialized a graph with size = 0 and empty list of vertices */
Graph* initGraph() {
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    new_graph->size = 0;
    new_graph->vertices = initList();
    new_graph->edges = initList();
    return new_graph;
}


#endif // GRAPH_H