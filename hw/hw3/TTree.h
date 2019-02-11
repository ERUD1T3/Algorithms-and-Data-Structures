#ifndef TTREE_H
#define TTREE_H

#include "SLinkedList.h"

#define SIZE 64
typedef struct tnode {
    char data[SIZE]; //data carried by node
    struct tnode* parent; //pointer to parent node
    struct tnode* children[SIZE]; //array of pointers to children node
} TNode;

typedef struct
{
    TNode* root; //pointer to root node of the tree
    uint size; //total number of nodes in the tree
    //uint height;
} TTree;


TTree* initTTree(); //initialize a Taxonomic tree
void destroy(TTree* to_del); //clear memory of Taxonomic tree
void insertRoot(TTree* tree); //inserts a new node into tree



TTree* initTTree() {
    /*
        Initialize a Taxonomic tree
    */
   TTree* new_tree = (TTree*)malloc(sizeof(TTree));
   new_tree->size = 0;
   new_tree->root = NULL;

   return new_tree;

}

void insertRoot(TTree* tree) {
    /*
    * Insert a new element into the tree
    */
}

void destroy(TTree* to_del) {
    /*
    * Clears the memory of the tree
    */
}


#endif //TTREE_H