#ifndef TTREE_H
#define TTREE_H

#include "SLinkedList.h"

#define SIZE 64

typedef struct tnode TNode; //predefinions of node
typedef struct tnlist TNList; // ...  of list
typedef struct ttree TTree; // ... of tree

struct tnode {
    char data[SIZE]; //data carried by node
    TNode* parent; //pointer to parent node
    //TNode* prev;
    TNode* next;
    TNList* children; //list of children
};

typedef struct tnlist {
    uint size; //size of the list
    TNode* head; //pointer to parent
};

typedef struct ttree {
    uint size; //total number of nodes in the tree
    TNode* root; //pointer to root node of the tree
    //uint height;
};

/****************************************
 * TNode Methods
 ***************************************/ 
TNode* initTNode(char* data, TNode* parent, TNList* children);
void destroyTNode(TNode* to_del); //clear memory of Taxonomic node





/*******************************************
 * TNList Methods
 ******************************************/

TNList* initTNList(); //initialize a list of TNodes
void destroyTNList(TNList* to_del); //clear memory of Taxonomic node
//Methods to operate on list
Node* traverse(TNList* List, const uint index);  //return the pointer to the node previous to the node at index 
void insert(TNList* List,const int index,const char* data); //_insert a node with payload data at position index
char* suppress(TNList* List,const int index);  //deletes a node at position index
void pushfront(TNList* List,const char* data); //_insert node at the front of the list
void pushback(TNList* List,const char* data); //_insert node at the end of the list
char* popfront(TNList* List);  //delete node at the back of the list
char* popback(TNList* List);  //delete node at the front of the list
void printlist(TNList* List); //print all elements in the list
char* getAt(TNList* List, const int index); //get the data at index 


char* getAt(TNList* List, const int index) {
    return (traverse(List, index)->data);
}

TNList* initList(void) {
    /*
    *   initialize size to 0 and head to NULL
    */
   TNList* List = (TNList*)malloc(sizeof(TNList));
   List->size = 0;
   List->head = NULL;
   return List;
}

void destroy(TNList* List) {
    while(List->size != 0) popback(List);
    free(List);
}

void printlist(TNList* List) {
    /*
    * print all elements in the list
    */
   if(List == NULL || List->size == 0 ) {
       printf("empty list\n");
       return;
   }
   printf("[");
   Node* tmp = List->head;

   if(List->size != 0) {
       while(tmp != NULL) {
           printf(" %s,", tmp->data);
           tmp = tmp->next;
       }
   }
   printf(" ]\n");
}

Node* traverse(TNList* List, const uint index) {
    /*
    * give an index N, _traverse() _traverse the list until N and return pointer to N-1
    * O(n)
    */
   
    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n"); 
        return NULL;
    }

    //case 2: index is not present
    if(index < 0 || index >= List->size) {
        printf("Invalid index!\n");
        return NULL;
    }

    //case 3: index present
    Node* tmp = List->head; 
    for(unsigned int i = 0; i < index; ++i) {//traversing till index - 1 
        //printf("tmp value: %d for i = %d\n ", tmp->data, i);    
        tmp = tmp->next; //moving to the next node
    }
    //printf("about to return\n");
    return tmp;
}

void insert(TNList* List, int index,const char* data) {
    /*
    * _insert a node with data at index
    * O(n)
    */

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->data,data);

    
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else if(index == 0) { //case 2: front _insertion
        new_node->next = List->head;
        List->head = new_node;
    } 
    else { //case 3: Non empty list with _insert at middle
        Node* prev = traverse(List, index);
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}


void pushfront(TNList* List,const char* data) {
    /*
    * _insert node at the front of the list
    */
   insert(List, 0, data);
} 

void pushback(TNList* List,const char* data) {
    /*
    * _insert node at the end of the list
    */
   if(List->size == 0) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        strcpy(new_node->data, data);
        new_node->next = NULL;
        List->head = new_node;
        ++List->size;
   }
   else if(List->size == 1) { //edge case for single node list
        Node* new_node = (Node*)malloc(sizeof(Node));
        strcpy(new_node->data, data);
        new_node->next = List->head->next;
        List->head->next = new_node;
        ++List->size;

    } else {
        insert(List, List->size - 1, data);
    }
}  


char* suppress(TNList* List,const int index) {
    /*
    * _suppress() deletes node at index
    * O(n)
    */ 

    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n");
        return NULL;
    }

    //case 2: invalid index
    if(index < 0 || index >= List->size) {
        printf("invalid index");
        return NULL;
    }

    Node* to_del;
    char* tmp = (char*)malloc(MAX_STR_SIZE*sizeof(char));
    
    if(index == 0) { //case 3: deleting head
       to_del = List->head;
       List->head = (List->head)->next;

    } else {  //case 4: deleting any node that is not head
        Node* prev = traverse(List, index - 1);
        to_del = prev->next;
        prev->next = to_del->next;

    }

    strcpy(tmp, to_del->data);
    free(to_del);
    --List->size;
    return tmp;
}

char* popfront(TNList* List) {
    /*
    * delete node at the back of the list
    */
    return suppress(List,0);
}  
char* popback(TNList* List) {
    /*
    * delete node at the front of the list
    */
    return suppress(List, List->size - 1);
}  

/*******************************************
 * TTree Methods
 ******************************************/
 
TTree* initTTree(); //initialize a Taxonomic tree
void destroyTTree(TTree* to_del); //clear memory of Taxonomic tree






void insertRoot(TTree* tree); //inserts a new node into tree


TNList* initTNList() {
    /*
    * initialize a list of TNodes
    */
    TNList* new_list = (TNList*)malloc(sizeof(TNList));
    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}

TNode* initNode(char* data, TNode* parent, TNList* children) {

    /*
    * Creates a new node for the tree
    */ 

    TNode* new_node = (TNode*)malloc(sizeof(TNode));
    strcpy(new_node->data, data);
    new_node->parent = parent;
    new_node->children = children;
    return new_node;
}




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