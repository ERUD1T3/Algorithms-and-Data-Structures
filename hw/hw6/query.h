/*****************************************
 * query.h 
 * Interface for processing commands from input file
 * Josias Moukpe
 ****************************************/


#ifndef QUERY_H
#define QUERY_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "sllist.h"



/*******************************
 * METHODS PROTOTYPES
 ******************************/

void buildGraph(Graph* network, SLList* friendships);
void processQuery(Graph* network, SLList* query_list);
void AddFriendship(Graph* network, char* user1, char* user2);
void RemoveFriendship(Graph* network, char* user1, char* user2);
void WantToBefriend(Graph* network, char* user1, char* user2);


/************************************************
 * METHODS IMPLEMENTATION
 ***********************************************/


/* adds edge between two user vertices */
void AddFriendship(Graph* network, char* user1, char* user2){
    return;
}

/* remove edge between two user vertices */
void RemoveFriendship(Graph* network, char* user, char* target) {
    return;
}

/* use an intermediate friend to create a new friendship */
void WantToBefriend(Graph* network, char* user1, char* user2) {
    return;
}


/* build a network graph based a friendship pairs */
void buildGraph(Graph* network, SLList* friendships) {

    char* user1_name = (char*)getAt(friendships, 0);
    char* user2_name = (char*)getAt(friendships, 1);

    // printf("\n In build garph, usernames: %s and %s", user1_name, user2_name);

    Vertex *user1 = initVertex(user1_name), *user2 = initVertex(user2_name);

    // printf("\n In build garph, vertex usernames: %s and %s", (char*)user1->data, (char*)user2->data);
    
    addVertex(network, user1);
    addVertex(network, user2);
    addEdge(user1, user2);
}   


/* Executes actions from the actions file */ 
void processQuery(Graph* network, SLList* query_list) {
    if(!strcmp((char*)getAt(query_list, 0), "AddFriendship")) 
        AddFriendship(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else if(!strcmp((char*)getAt(query_list, 0), "RemoveFriendship")) 
        RemoveFriendship(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else if(!strcmp((char*)getAt(query_list, 0), "WantToBefriend")) 
        WantToBefriend(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else 
        printf("Invalid command!\n");
    destroyList(query_list);
}

#endif // QUERY_H