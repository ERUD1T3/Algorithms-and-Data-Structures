/************************************
 * GRAPH INTERFACE FOR HW6
 * Josias Moukpe
 ************************************/ 
#ifndef GRAPH_H
#define GRAPH_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"



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
    // uint size;
    SLList* vertices;
    // SLList* edges;  
};


/********************************
 * PROTOTYPE METHODS
 *******************************/

Vertex* initVertex(void* data);
Graph* initGraph();
void addVertex(Graph* graph, Vertex* vertex);
void removeVertex(Graph* graph, Vertex* vertex);
void addEdge(Vertex* vertex1, Vertex* vertex2);
void removeEdge(Vertex* vertex1, Vertex* vertex2);
Vertex* searchUser(Graph* graph, char* name);
void printVertices(SLList* vertices);
SLList* pathBFS(Graph* graph, Vertex* source, Vertex* destination);
void insortVertex(SLList* List,  void* data);

/********************************
 * METHODS IMPLEMENTATION
 *******************************/ 

/* insert a node with data at index */
void insortVertex(SLList* List,  void* data) {
    Node* new_node = initNode(data);
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else 
    if(strcmp((char*)((Vertex*)List->head->data)->data, (char*)((Vertex*)data)->data) > 0) { // inserting before the head
        new_node->next = List->head;
        List->head = new_node;
    }   
    else { // case 3: insert sort

        Node* prev = List->head;
        while(prev->next != NULL && 
        (strcmp((char*)((Vertex*)prev->next->data)->data, (char*)((Vertex*)data)->data) < 0)) 
            prev = prev->next;
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}


/* searches the graph for a user and return the pointer of its vertex if found and NULL otherwise */
Vertex* searchUser(Graph* graph, char* name) {
    // if(graph->size == 0) return NULL;
    for(Node* curr = graph->vertices->head; curr != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->data)->data;
        // printf("\nname: %s vs to_comp: %s", name, to_comp);
        if(!strcmp(to_comp, name)) return (Vertex*)curr->data;
          
    }
    return NULL;
}


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
    // new_graph->size = 0;
    new_graph->vertices = initList();
    // new_graph->edges = initList();
    return new_graph;
}

/* add new egde between two vertices */
void addEdge(Vertex* vertex1, Vertex* vertex2) {
    insortVertex(vertex1->adj_node, vertex2);
    insortVertex(vertex2->adj_node, vertex1);
}


/* add a new vertex to the graph */
void addVertex(Graph* graph, Vertex* vertex) {
    char* name_to_search = (char*)vertex->data;
    // printf("\nname to search is: %s", name_to_search)
    if(searchUser(graph, name_to_search) == NULL) {
        insortVertex(graph->vertices, vertex);
        // printf("|vertices| = %d", graph->vertices->size);
        // ++graph->size;
    }
}

/* print vertices in a graph */
void printVertices(SLList* vertices) {
    if(vertices == NULL || vertices->size == 0 ) {
        printf("empty list\n");
        return;
    }

    // printf("\nbegin/");
    if(vertices->size != 0) {
        for(Node* tmp = vertices->head; tmp != NULL; tmp = tmp->next) {
            char* to_print = (char*)((Vertex*)tmp->data)->data;
            printf("%s ", to_print);
        }
    }
    // printf("/end\n");
}

#endif // GRAPH_H