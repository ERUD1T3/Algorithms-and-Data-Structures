#ifndef TTREE_H
#define TTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TNList.h" //for TNode and TNList


typedef struct ttree TTree; // ... of tree

struct ttree {
    uint size;
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
TNode* getChild(TNList* children,  uint index);
void addChild(TNode* parent,  char* child);
void insertNode(TTree* tree, TNode* node, TNode* parent); //inserts a new node into tree
void printTTree(TTree* taxonomy);
void buildTTree(TTree* taxonomy, TNList* data_list); //insert a new node in Tree
//void insertTNode(TTree* taxonomy, TNList* data_list); //insert a new node in Tree
TNode* searchNode(TTree* taxonomy,  char* data); //search the tree for node containing data
void insertChild( char* child_data, TNode* parent);
void preOrder(TNode* root);
TNode* preOrderSearch(TNode* root, char* key);
void recDestroy(TNode* root); //recursively destroy all nodes in tree

/*******************************************
 * TTree Methods
 ******************************************/


TNode* searchNode(TTree* taxonomy, char* data) {
    /*
    * Search the tree for data node and return the pointer to the data node
    */ 
  return preOrderSearch(taxonomy->root, data);
}

void buildTTree(TTree* taxonomy, TNList* data_list) {

    /*
    * build a tree with the data_list
    * parent data is getAt(data_list, 0)
    * children data is getAt(data_list, 1 to data_list->size -1)
    */ 

    if (taxonomy->root == NULL) {
        //char* tmp = getAt(data_list, 0);
        taxonomy->root = initTNode(getAt(data_list, 0), NULL, initTNList());
        for(uint i = 1; i < data_list->size; ++i) { //adding children
            //taxonomy->root->children = initTNList();
            insertChild(getAt(data_list, i), taxonomy->root);
        }

    } 
    else { //inserting non -root position
        char* tmp_data  = getAt(data_list, 0);
        TNode* parent = searchNode(taxonomy, tmp_data);
        //printf("we are now inserting at %s\n\n", parent->data);
        for(uint i = 1; i < data_list->size; ++i) { //adding children
            //taxonomy->root->children = initTNList();
            insertChild(getAt(data_list, i), parent);
        }
    }
    
    destroyTNList(data_list); //clear space created by datalist
}


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

TNode* getChild(TNList* children,  uint index) {
    /*
    * Returns a pointer to a specific child in the list of Children
    */
    return (traverse(children, index));
}

void addChild(TNode* parent,  char* child_data) {
    /*
    * Adds a child node to parent list of children
    */
    insertChild(child_data, parent);
}

// void insertTNode(TTree* taxonomy, TNode* node, TNode* parent) {
//     if(taxonomy == NULL) {
//         printf("NULL tree");
//         return;
//     }

//     if(taxonomy->allnodes->size == 0) { //adding root
//         taxonomy->root = node;
//         node->parent = NULL;
//         node->children = NULL;
//     } 
//     else { //adding a child
//         TNode* tmp = taxonomy->allnodes->head;
//         //while(tmp->next != NULL && ) tmp
//     }

//     //insertSort(taxonomy->allnodes, node);
// }


void preOrder(TNode* root) {
    if(root == NULL) return;
    printf("%s ", root->data);

    for(uint i = 0; i < root->children->size; ++i) {
        preOrder(getChild(root->children, i));
    }
}

TNode* preOrderSearch(TNode* root, char* key) {
    /*
    * search the tree for a value.
    */ 
    if(!strcmp(root->data, key)) return root;

    for(uint i = 0; i < root->children->size; ++i) {
        TNode* child = getChild(root->children, i);
        TNode* tmp = preOrderSearch(child, key);
        if(tmp != NULL) return tmp;
        //else if(!strcmp(tmp->data, key)) return tmp;
        //else return tmp;
    }
    return NULL;
}

void printTTree(TTree* taxonomy) {
    /*
    * calles preOrder to print the tree
    */ 
    preOrder(taxonomy->root);
    printf("\n");
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

void recDestroy(TNode* root) {
    for(uint i = 0; i < root->children->size; ++i) {
        recDestroy(getChild(root->children, i));
    }
    
    if(root == NULL) return;
    destroyTNode(root);   
}

void destroyTTree(TTree* to_del) {
    /*
    * Traverses the tree to delete all its nodes Clears the memory of the tree
    */
    recDestroy(to_del->root);
    free(to_del);
}

void insertChild(char* child_data, TNode* parent) {
    /*
    Insert node at right position
    */  
    TNode* child = initTNode(child_data, parent, initTNList());

    if(parent->children == NULL) {
        printf("Cannot insert in null list");
        return;
    }

    if(parent->children->size == 0) { //case 1: empty children
        parent->children->head = child;
        child->next = NULL;
    } 
    else 
    if(strcmp(parent->children->head->data, child->data) > 0) { //case 2: front _insertion
        child->next = parent->children->head;
        parent->children->head = child;
    } 
    else { //case 3: Non empty children with insert at middle
        TNode* prev = parent->children->head;
        while(prev->next != NULL && (strcmp(prev->next->data, child->data) < 0)) prev = prev->next;
        child->next = prev->next;
        prev->next = child;
    }

    ++(parent->children->size);
}


#endif //TTREE_H