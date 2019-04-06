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
    bool is_visited;
    void* data;
    SLList* adj_nodes;
    Vertex* prev; // previous vertex in BFS
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
Vertex* searchUser(SLList* userlist, char* name); // TODO: improve using binary search
void deleteAdj(SLList* adjlist, char* name); // TODO: improve using binary search
void printVertices(SLList* vertices);
// SLList* pathDFS(Graph* graph, Vertex* source, Vertex* destination, SLList* stack);
void insortVertex(SLList* List,  void* data);
bool isAdjacent(Vertex* src, Vertex* target);
void destroyGraph();
SLList* shortestPath(Graph* graph, Vertex* src, Vertex* dest);



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


/* return the node previous to the found node */
void deleteAdj(SLList* adjlist, char* name) {
    // printf("name is delete is %s", name);
    if(adjlist->size == 0) {
        printf("empty list");
        return;
    }
    Node* to_del = NULL, *prev = NULL;
    char* to_comp = (char*)((Vertex*)adjlist->head->data)->data;
    if(!strcmp(to_comp, name)) {
        // printf("name is %s, to_comp is %s", name, to_comp);
        to_del = adjlist->head;
        adjlist->head = to_del->next;
        free(to_del);
        return;
    }
    for(Node* curr = adjlist->head; curr->next != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->next->data)->data;
        // printf("\nname: %s vs to_comp: %s", name, to_comp);
        if(!strcmp(to_comp, name)) {
            prev = curr;
            to_del = curr->next;
            break;
        }
    }

    prev->next = to_del->next;
    free(to_del);
}





/* removes edge between two vertices */
void removeEdge(Vertex* vertex1, Vertex* vertex2) {
    if(!isAdjacent(vertex1, vertex2) || !isAdjacent(vertex2, vertex1)) 
    {
        printf("No FriendshipError");
        return;
    }

    deleteAdj(vertex1->adj_nodes, (char*)vertex2->data);
    deleteAdj(vertex2->adj_nodes, (char*)vertex1->data);
    
}

/* returns true if target is adjacent to source */
bool isAdjacent(Vertex* src, Vertex* target) {
    for(Node* curr = src->adj_nodes->head; curr != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->data)->data;
        // printf("\nname: %s vs to_comp: %s", name, to_comp);
        if(!strcmp(to_comp, (char*)target->data)) return true;
          
    }
    return false;
}


/* clear graph memory */
void destroyGraph() {
    return;
}



/* searches the graph for a user and return the pointer of its vertex if found and NULL otherwise */
Vertex* searchUser(SLList* userlist, char* name) {
    // if(graph->size == 0) return NULL;
    for(Node* curr = userlist->head; curr != NULL; curr = curr->next) {
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
    new_node->is_visited = false;
    new_node->adj_nodes = initList(); 
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
    if(isAdjacent(vertex1, vertex2) || isAdjacent(vertex2, vertex1)) 
    {
        printf("ExistingFriendshipError");
        return;
    }
    insortVertex(vertex2->adj_nodes, vertex1);
    insortVertex(vertex1->adj_nodes, vertex2);
}


/* add a new vertex to the graph */
void addVertex(Graph* graph, Vertex* vertex) {
    //char* name_to_search = (char*)vertex->data;
    // printf("\nname to search is: %s", name_to_search)
    //if(searchUser(graph->vertices, name_to_search) == NULL) {
        insortVertex(graph->vertices, vertex);
        // printf("|vertices| = %d", graph->vertices->size);
        // ++graph->size;
    //}
}

/* print vertices in a graph */
void printVertices(SLList* vertices) {
    if(vertices == NULL || vertices->size == 0 ) {
        printf("empty list");
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

// SLList* pathDFS(Graph* graph, Vertex* src, Vertex* dest, SLList* stack) {
//     src->is_visited = true;
//     pushfront(stack, src);

//     if(!strcmp((char*)src->data, (char*)dest->data)) {
//         return stack;
//     }

//     SLList* path = NULL;
//     SLList* neighbors = src->adj_nodes;
//     for(Node* curr = neighbors->head; curr != NULL; curr = curr->next) {
//         Vertex* adj = (Vertex*)curr->data;
//         if(!(adj->is_visited)) {
//             path = pathDFS(graph, adj, dest, stack);
//             if(path != NULL) return path;
//         }

       

//     }
//     popfront(stack);
//     return NULL;
// }


SLList* shortestPath(Graph* graph, Vertex* src, Vertex* dest) {
    Vertex* curr = NULL;
    SLList* queue = initList();
    SLList* path = initList();
    
    pushback(queue, src);
    while(queue->size != 0) {
        curr = (Vertex*)popfront(queue);
        if(!(curr->is_visited)) {

        }
    }
    return path;
}

#endif // GRAPH_H