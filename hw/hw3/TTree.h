#ifndef TTREE_H
#define TTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TNList.h" //for TNode and TNList


typedef struct ttree TTree; // ... of tree

struct ttree {
    struct tnode* root; //pointer to root node of the tree
    struct tnlist* allnodes; //list of all nodes present in the tree
};

/****************************************
 * METHODS PROTOTYPES
 ***************************************/ 

TTree* initTTree(); //initialize a Taxonomic tree
void destroyTTree(TTree* to_del); //clear memory of Taxonomic tree
TNList* getChildren(TNode* parent);
TNode* getParent(TNode* child);
TNode* getChild(TNList* children, const uint index);
void addChild(TNode* parent, TNode* child);
void insertNode(TTree* tree, TNode* node, TNode* parent); //inserts a new node into tree
void printTTree(TTree* taxonomy);
void buildTTree(TTree* taxonomy, TNList* data_list); //insert a new node in Tree
//void insertTNode(TTree* taxonomy, TNList* data_list); //insert a new node in Tree
TNode* search(TTree* taxonomy, const char* data); //search the tree for node containing data

void preOrder(TNode* root);


/*******************************************
 * TTree Methods
 ******************************************/

TNode* getParent(TNode* child) {
    /*
    * Return a pointer to the parent node
    */ 
   return child->parent;
}

TNList* getChildren(TNode* parent) {
    /*
    * Return a pointer to the children list of a node
    */ 
   return parent->children;
}

TNode* getChild(TNList* children, const uint index) {
    /*
    * Returns a pointer to a specific child in the list of Children
    */
    return (traverse(children, index));
}

void addChild(TNode* parent, TNode* child) {
    /*
    * Adds a child node to parent list of children
    */
    insertSort(parent->children, child);
    child->parent = parent;
}


void buildTTree(TTree* taxonomy, TNList* data_list) {

    if (taxonomy->root == NULL) {
        //char* tmp = getAt(data_list, 0);
        taxonomy->root = initTNode(getAt(data_list, 0), NULL, NULL);

        //adding children
        for(uint i = 1; i < data_list->size; ++i) {
            taxonomy->root->children = initTNList();
            // insertSort(taxonomy->root->children, getAt(data_list, i), taxonomy->root);
        }

    }
    
    destroyTNList(data_list); //clear space created by datalist
}


void insertTNode(TTree* taxonomy, TNode* node, TNode* parent) {
    if(taxonomy == NULL) {
        printf("NULL tree");
        return;
    }

    if(taxonomy->allnodes->size == 0) { //adding root
        taxonomy->root = node;
        node->parent = NULL;
        node->children = NULL;
    } 
    else { //adding a child
        TNode* tmp = taxonomy->allnodes->head;
        //while(tmp->next != NULL && ) tmp
    }

    insertSort(taxonomy->allnodes, node);
}


void preOrder(TNode* root) {
    if(root == NULL) return;
    printf("%s", root->data);
    for(uint i = 0; i < root->children->size; ++i) {
        preOrder(getChild(root->children, i));
    }
}


void printTTree(TTree* taxonomy) {
    preOrder(taxonomy->root);
}

TTree* initTTree() {
    /*
        Initialize a Taxonomic tree and return its pointer
    */
   TTree* new_tree = (TTree*)malloc(sizeof(TTree));
   new_tree->root = NULL;
   new_tree->allnodes = initTNList();

   return new_tree;

}

void destroyTTree(TTree* to_del) {
    /*
    * Traverses the tree to delete all its nodes Clears the memory of the tree
    */
    destroyTNList(to_del->allnodes);
    free(to_del);
}


#endif //TTREE_H