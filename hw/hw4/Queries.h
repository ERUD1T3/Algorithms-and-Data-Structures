#ifndef QUERIES_H
#define QUERIES_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TNList.h"
#include "Heap.h"


/*******************************
 * METHODS
 ******************************/

void EnterBid(Heap* pQueue, uint time, char* name, float price, uint quantity) {

}

void UpdateMinimumAcceptablePrice(Heap* pQueue, uint time, float price) {
    pQueue->min_price = price;
}

void SellOneItem(Heap* pQueue, uint time) {

}

void DisplayHighestBid(Heap* pQueue, uint time) {

}

void processQuery(Heap* pQueue, TNList* query_list) {
    /*
    *   Executes the right query on the Taxonomy tree
    */ 

    if(!strcmp(getAt(query_list, 0), "UpdateMinimumAcceptablePrice")) {
        UpdateMinimumAcceptablePrice(pQueue, 
            atoi(getAt(query_list, 1)), 
            atoi(getAt(query_list, 2))
            );
    }
    else 
    if(!strcmp(getAt(query_list, 0), "EnterBid")) {
        EnterBid(pQueue, 
            atoi(getAt(query_list, 1)), 
            getAt(query_list, 2), 
            atoi(getAt(query_list, 3)), 
            atoi(getAt(query_list, 4))
            );
    }
    else 
    if(!strcmp(getAt(query_list, 0), "DisplayHighestBid")) {
        DisplayHighestBid(pQueue, atoi(getAt(query_list, 1)));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "SellOneItem")) {
        SellOneItem(pQueue, atoi(getAt(query_list, 1)));
    }
    else printf("Invalid command!\n");
}

#endif // QUERIES_H