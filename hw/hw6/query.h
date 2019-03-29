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
#include "sllist.h"
#include "graph.h"


/*******************************
 * METHODS PROTOTYPES
 ******************************/

void processQuery(Graph* , SLList* query_list);
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
void WantToBefriend(Graph* network) {
    return;
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