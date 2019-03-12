#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32 // max size
#define MAX_SIZE 100 // max number of nodes in the heap

typedef unsigned int uint; // alias to unsigned integer
typedef struct bid Bid; // alias to bid structure
typedef struct heap Heap; // alias to heap

struct bid {
    float price;
    uint timestamp; // bid keys
    uint quantity;
    char customer_name[SIZE]; // bid value
};

struct heap {
    uint min_price;
    uint size; // total number of nodes in the tree
    Bid* arrBids[MAX_SIZE];
};


/**************************************
 * METHODS
 *************************************/ 

uint getLeftChildIndex(const uint parent_index) {
    return (2 * parent_index + 1);
}

uint getRightChildIndex(const uint parent_index) {
    return (2 * parent_index + 2);
}

uint getParentIndex(const uint child_index) {
    return (child_index - 1)/2;
}

void swap(Heap* pQueue, uint a_index, uint b_index) {
    Bid* tmp = pQueue->arrBids[a_index];
    pQueue->arrBids[a_index] = pQueue->arrBids[b_index];
    pQueue->arrBids[b_index] = tmp;
}

void Heapify(Heap* pQueue) {
    // propagate the smallest element to the top
}


Bid* initBid(uint price, uint timestamp, uint quantity, char* cust_name) {
    Bid* new_bid = (Bid*)malloc(sizeof(Bid));

    strcpy(new_bid->customer_name, cust_name);
    new_bid->price = price;
    new_bid->timestamp = timestamp;
    new_bid->quantity = quantity;
    return new_bid;
}

Heap* initHeap(void) {
    Heap* new_pqueue = (Heap*)malloc(sizeof(Heap));
    new_pqueue->size = 0;
    new_pqueue->min_price = 0;
    for(uint i = 0; i < MAX_SIZE; ++i) new_pqueue->arrBids[i] = NULL;
    return new_pqueue;
}

void insertHeap(Heap* pQueue, Bid* entry) {

}


Bid* removeMax(Heap* pQueue) { // return and remove entry with the maximum key

}

Bid* getMax(Heap* pQueue) { // return entry with the maximum key
    if(pQueue->size != 0) return *(pQueue->arrBids); 
    else {
        printf("empty Priority Queue! \n");
        return NULL;
    }
    // return (pQueue->arrBids)[0];
}

bool isFull(Heap* pQueue) {
    return (pQueue->size == MAX_SIZE);
}

bool isEmpty(Heap* pQueue) {
    return (pQueue->size == 0);
}

#endif // HEAP_H