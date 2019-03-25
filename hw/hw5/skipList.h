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
int getRandHeight(); //pseudo randomly assign level for insertion
Entry* initEntry(uint time, char* activity);
SNode* initSNode(Entry* act_log, uint ins_level, SNode* next, SNode* prev, SNode* above, SNode* below);
void addEmptyLevel(SList* skip_list);
void insertInLevel(SNode* head, SNode* to_insert); /* Insert key-value pair in ordered list */
void deleteDown(SNode* top_occ); /* deletes nodes down, starting at the top occurence of the entry */
void displayLevel(SNode* head); /* display all nodes in level */
SList* initSList();
void printList(SList* skip_list); 
char* getEvent(SList* skip_list, uint key); // if key exists, return value associated with key; otherwise, return NULL
SNode* findEvent(SList* skip_list, uint key);
char* putEvent(SList* skip_list, uint key, char* value); // if key doesn’t exist, add entry and return NULL; otherwise, replace value and return the old value
char* removeEvent(SList* skip_list, uint key); // if key exists, remove entry and return its value; otherwise, return NULL
SNode* ceilingEntry(SList* skip_list, uint key); // return the entry with the smallest key greater than or equal to key; return NULL if no such entry exists
SNode* floorEntry(SList* skip_list, uint key); // return the entry with the largest key less than or equal to key; return NULL if no such entry exists
SList* subMap(SList* skip_list, uint key1, uint key2); // return all entries with key such that key1 ≤ key ≤ key2
void destroySList(SList* skip_list);

/***********************************************
 * METHODS IMPLEMENTATION
 **********************************************/

void destroySList(SList* skip_list) {


}

/* return entry with smallest key >= key */
SNode* ceilingEntry(SList* skip_list, uint key) {
    if(skip_list->size != 0) {
        SNode* tmp = skip_list->ceiling_head;
        while(tmp != skip_list->floor_tail) { 
            if(tmp->next->entry == NULL) {
                tmp = tmp->below; // going down the list
            } else 
            if(tmp->next->entry->time > key) {
                tmp = tmp->below; // going down the list
            } else 
            if(tmp->next->entry->time <= key) {
                tmp = tmp->next;
            } else 
            if(tmp->next->entry->time == key) {
                return tmp->next;
            } else {
            }
        }
    }
    return NULL; //key wasn't found
}


// MOSTLY DONE

/* deletes nodes down, starting at the top occurence of the entry */
void deleteDown(SNode* top_occ) {
    // SNode* next = NULL;
    for(SNode* to_del = top_occ, *next = NULL; to_del != NULL; to_del = next) {
        next = to_del->below;
        to_del->prev->next = to_del->next;
        to_del->next->prev = to_del->prev;
        free(to_del);      
    }
}

/* remove an entry and all its instances from the list */
char* removeEvent(SList* skip_list, uint key) {
    SNode* target = findEvent(skip_list, key);
    if(target != NULL) {
        char* old_val = (char*)malloc(SIZE*sizeof(char));
        strcpy(old_val, target->entry->activity);
        deleteDown(target);
        --skip_list->size;
        return old_val;
    }
    return NULL; // key to delete not found
}


/* display all nodes in level */
void displayLevel(SNode* head) {
    if(head->next->entry == NULL) {
        printf("Empty");
        return;
    }
    for(SNode* node = head->next; node->entry != NULL; node = node->next) {
        printf("%d:%s ", node->entry->time, node->entry->activity);
    }
}

/* insert an SNode into a level of the skip_list */
void insertInLevel(SNode* head,  SNode* to_insert) {
   
    for(SNode* tmp = head; tmp->next != NULL; tmp = tmp->next) {
        if(tmp->next->entry == NULL) { // reached the end without finding larger entry
            to_insert->next = tmp->next;
            to_insert->prev = tmp;
            tmp->next = to_insert;
            to_insert->next->prev = to_insert;
            return;
        } 
        if(tmp->next->entry->time >= to_insert->entry->time) { // found a larger entry key // equal case should theoretically not occur
            to_insert->next = tmp->next;
            to_insert->prev = tmp;
            tmp->next = to_insert;
            to_insert->next->prev = to_insert;
            return;
        }
    }
}

/* Insert new entry into the skip list */
char* putEvent(SList* skip_list, uint key, char* value) {

    uint insert_level = getRandHeight(); // implicit conversion from int to unsigned int

    while(insert_level >= skip_list->height) { // inserting toward a height larger than prev height
        addEmptyLevel(skip_list); // add a new layer
    }
    
    SNode* target = findEvent(skip_list, key);
    // Entry* new_entry = ;

    if(target == NULL) { // inserting new node
        Entry* new_entry = initEntry(key, value);
        SNode* to_insert[insert_level + 1];

        for(uint level = 0; level <= insert_level; ++level) {
            to_insert[level] = initSNode(new_entry, level, NULL, NULL, NULL, NULL);
        }
        for(uint level = 0; level <= insert_level; ++level) { 
            to_insert[level]->below = (level == 0) ? NULL: to_insert[level-1];
            to_insert[level]->above = (level == insert_level) ? NULL : to_insert[level+1];
        }

        for(SNode* head = skip_list->floor_head; head->level <= insert_level; head = head->above) {
            insertInLevel(head, to_insert[head->level]);
        }
        ++skip_list->size;
        return NULL;
    }
    else { // overwriting previous entry
        char* old_val = (char*)malloc(SIZE*sizeof(char));
        strcpy(old_val, target->entry->activity);
        strcpy(target->entry->activity, value);
        return old_val;
    }
    
}

/* returns the pointer to the node with key */
char* getEvent(SList* skip_list, uint key) {
    return findEvent(skip_list, key)->entry->activity;
}

/* finds an event in a skip list */
SNode* findEvent(SList* skip_list, uint key) {
    if(skip_list->size != 0) {
        SNode* tmp = skip_list->ceiling_head;
        while(tmp != NULL && tmp != skip_list->floor_tail) { 
            if(tmp->entry != NULL) {
                if(tmp->entry->time == key) return tmp->next;
                else 
                if(tmp->entry->time > key) {
                    tmp = tmp->prev; //go back one step
                    tmp = tmp->below; // going down the list
                } 
                else  tmp = tmp->next; // move forward
            } 
            else { // tmp->entry == NULL

                if(tmp->prev != NULL) tmp = tmp->prev; //go back one step
                tmp = tmp->below; // going down the list
            }  
        }
    }
    return NULL; //key wasn't found
}

/* prints a skip list */
void printList(SList* skip_list) {
    printf("\n");
    if(skip_list->size == 0) {
        printf("Empty skip list!");
        return;
    }

    for(SNode* level_head = skip_list->ceiling_head; level_head != NULL; level_head = level_head->below) {
        printf("(S%d) ", level_head->level);
            // if(level_head->next->entry == NULL) {
            //     printf("Empty\n");
            //     continue;
            // }
            // for(SNode* node = level_head->next; node->entry != NULL; node = node->next) {
            //     printf("%d:%s ", node->entry->time, node->entry->activity);
            // }
        displayLevel(level_head);
        printf("\n");
    }
}

/* add an empty level to the list */
void addEmptyLevel(SList* skip_list) {
    
    ++skip_list->height;
    skip_list->ceiling_head = initSNode(NULL, skip_list->height, NULL, NULL, NULL, skip_list->ceiling_head);
    skip_list->ceiling_tail = initSNode(NULL, skip_list->height, NULL, NULL, NULL, skip_list->ceiling_tail);
    skip_list->ceiling_head->next = skip_list->ceiling_tail;
    skip_list->ceiling_tail->prev = skip_list->ceiling_head;
    skip_list->ceiling_head->below->above = skip_list->ceiling_head;
    skip_list->ceiling_tail->below->above = skip_list->ceiling_tail;
}

/* initializes an entry */
Entry* initEntry(uint time, char* activity) {
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->activity = (char*)malloc(SIZE*sizeof(char));
    strcpy(new_entry->activity, activity);
    new_entry->time = time;
    return new_entry;
}

/* initializes an SNode */
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

/* return a pseudo random height */
int getRandHeight() {
  static int height[] = {0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, // sequence of height
                         0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
  
  static int count=0;  // number of times getRandHeight() has been called 

  return height[count++ % 31];
}




#endif // SKIPLIST_H