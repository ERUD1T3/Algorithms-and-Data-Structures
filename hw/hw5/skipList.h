/*****************************************
 * skipList.h 
 * Interface of skiplist
 ****************************************/

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define PLUS_INF NULL
// #define MINUS_INF NULL
#define INF NULL // only infinities have null entries
#define SIZE 32
#define MAX_LEVEL 4

typedef unsigned int uint;
typedef struct entry Entry;
typedef struct skip_node SNode;
// typedef struct level_list LList;
typedef struct skip_list SList;

struct entry {
    uint time;
    char* activity;
};

struct skip_node {
    uint level; // track the level in which node is 
    Entry* entry; // container for the entry entry
    SNode *prev, *next, *below, *above;
};

// struct level_list {
//     uint size, level;
//     SNode *head, *tail;
// };

struct skip_list {
    uint size, height; // size represent total number of nodes, height represent number of levels
    SNode *floor_head, *ceiling_head, *floor_tail, *ceiling_tail; // floor is the bottom level, ceiling is top level
};


/*************************************************
 * METHODS PROTOTYPES
 ***********************************************/

SNode* getEvent(SList* skip_list, uint key); // if key exists, return value associated with key; otherwise, return NULL
char* putEvent(SList* skip_list, uint key, char* value); // if key doesn’t exist, add entry and return NULL; otherwise, replace value and return the old value
char* removeEvent(SList* skip_list, uint key); // if key exists, remove entry and return its value; otherwise, return NULL
SNode* ceilingEntry(SList* skip_list, uint key); // return the entry with the smallest key greater than or equal to key; return NULL if no such entry exists
SNode* floorEntry(SList* skip_list, uint key); // return the entry with the largest key less than or equal to key; return NULL if no such entry exists
SList* subMap(SList* skip_list, uint key1, uint key2); // return all entries with key such that key1 ≤ key ≤ key2
int getRandHeight(); //pseudo randomly assign level for insertion
Entry* initEntry(uint time, char* activity);
SNode* initSNode(Entry* act_log, uint ins_level, SNode* next, SNode* prev, SNode* above, SNode* below);
void addEmptyLevel(SList* skip_list);
void insert(SNode* head, SNode* to_insert); /* Insert key-value pair in ordered list */
// SNode* trvrs(SNode* head,  uint index);
// LList* initLList();
SList* initSList();


/***********************************************
 * METHODS IMPLEMENTATION
 **********************************************/

// SNode* trvrs(SNode* head,  uint index) {
//     /*
//     * give an index N, _traverse() _traverse the list until N and return pointer to N-1
//     * O(n)
//     */

//     // case 1: empty list
//     if(head == NULL) {
//         printf("empty list!\n"); 
//         return NULL;
//     }
//     // case 2: index is not present
//     if(index >= List->size) {
//         printf("Invalid index!\n");
//         return NULL;
//     }

//     // case 3: index present
     
//     for(SNode* tmp = head; tmp->entry->time < index; tmp = tmp->next) 

//     return tmp;
// }

void insert(SNode* head,  SNode* tail, SNode* to_insert) {
    /*
    * _insert a node with data at index
    * O(n)
    */

    // Node* new_node = initNode(data);
    // strcpy((char*)(new_node->data),data);

    
    // if(List->size == 0) { //case 1: empty list
    //     List->head = new_node;
    //     new_node->next = NULL;
    // } 
    // else 
    if(head->next == tail) { // empty list with only NULL entry head and tail
        to_insert->next = tail;
        head->next = to_insert;
    
    } 
    else { // insert at proper place
        // Node* prev = traverse(List, index);
        // new_node->next = prev->next;
        // prev->next = new_node;
        //  for(SNode* tmp = head; tmp->entry->time < index; tmp = tmp->next) 
    }

}

/* add an empty level to the list */
void addEmptyLevel(SList* skip_list) {
    
    ++skip_list->height;
    skip_list->ceiling_head = initSNode(NULL, skip_list->height, NULL, NULL, NULL, skip_list->ceiling_head);
    skip_list->ceiling_tail = initSNode(NULL, skip_list->height, NULL, NULL, NULL, skip_list->ceiling_tail);
    skip_list->ceiling_head->next = skip_list->ceiling_tail;
    skip_list->ceiling_tail->prev = skip_list->ceiling_head;
}


Entry* initEntry(uint time, char* activity) {
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->activity = (char*)malloc(SIZE*sizeof(char));
    strcpy(new_entry->activity, activity);
    new_entry->time = time;
    return new_entry;
}

SNode* initSNode(Entry* act_log, uint ins_level, SNode* next, SNode* prev, SNode* above, SNode* below) {
    SNode* new_node = (SNode*)malloc(sizeof(SNode));

    if (new_node == NULL)
    {
      printf("malloc failed, memory is full\n");
      exit(-1);
    }

    new_node->above = above;
    new_node->below = below;
    new_node->prev = prev;
    new_node->next = next;
    new_node->entry = act_log;
    new_node->level = ins_level;
    return new_node;
}

// LList* initLList() {
//     LList* new_list = (LList*)malloc(sizeof(LList));
//     new_list->size = 0;
//     new_list->level = 0;
//     new_list->head = NULL;
//     new_list->tail = NULL;  
//     return new_list ;
// }

/* initialize a new list with 0 size and height */
SList* initSList() { 
    /*
    * Starts a skip list with one level with 2 infinity nodes
    */ 

    SList* new_list = (SList*)malloc(sizeof(SList));
    new_list->size = 0;
    new_list->height = 0;
    // new_list->ceiling_head = NULL;
    // new_list->ceiling_tail = NULL;
    new_list->floor_head = initSNode(INF, 0, NULL, NULL, NULL, NULL);   
    new_list->floor_tail = initSNode(INF, 0, NULL, NULL, NULL, NULL);   
    new_list->floor_head->next = new_list->floor_tail;
    new_list->floor_tail->prev = new_list->floor_head;
    new_list->ceiling_head = new_list->floor_head;
    new_list->ceiling_tail = new_list->floor_tail;
    return new_list;
}

int getRandHeight() {
  static int height[] = {0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, // sequence of height
                         0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
  
  static int count=0;  // number of times getRandHeight() has been called 

  return height[count++ % 31];
}


/* Insert new entry into the skip list */
char* putEvent(SList* skip_list, uint key, char* value) {
    ++skip_list->size;
    uint insert_level = getRandHeight(); // implicit conversion from int to unsigned int
    while(insert_level > skip_list->height) { // inserting toward a height larger than prev height
        addEmptyLevel(skip_list); // add a new layer
    }
    
    SNode* target = getEvent(skip_list, key);
    // Entry* new_entry = ;

    if( target == NULL) { // inserting new node
        for(uint level = 0; level <= insert_level; ++level) {
        // SNode* to_insert = initSNode(initEntry(key, value), level, )

        }

        return NULL;
    }
    else { // overwriting previous entry
        char* old_val = (char*)malloc(SIZE*sizeof(char));
        strcpy(old_val, target->entry->activity);
        strcpy(target->entry->activity, value);

        return old_val;
    }
}
    // SNode* new_node = initSNode(initEntry(key, value), 0)


    /* returns the pointer to the node with key */
SNode* getEvent(SList* skip_list, uint key) {

    
}

#endif // SKIPLIST_H