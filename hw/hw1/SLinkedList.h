//Copyright to Josias Moukpe, 2019

#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "utils.h"

#define TRUE 1
#define FALSE 0
#define MAX_STRING_SIZE 64

typedef struct node {
    /*
    * Node for single linked list structure
    */
    char data[MAX_STRING_SIZE]; //data contained in node
    //char* data;
    struct node* next; //pointer to next node

} Node;

typedef struct {
    /*
    * Single Linked List struct
    */ 
   int size; //overall size of Single Linked List
   Node* head; //pointer to first element in the list

} SLList;


//Methods to operate on list
void init(SLList* List); //initialize data member of the list
Node* traverse(SLList* List,const int index);  //return the pointer to the node previous to the node at index 
void insert(SLList* List,const int index,const char* data); //insert a node with payload data at position index
void suppress(SLList* List,const int index);  //deletes a node at position index
void pushfront(SLList* List,const char* data); //insert node at the front of the list
void pushback(SLList* List,const char* data); //insert node at the end of the list
void popfront(SLList* List);  //delete node at the back of the list
void popback(SLList* List);  //delete node at the front of the list
void printlist(SLList* List); //print all elements in the list
char* getAt(SLList* List, const int index); //get the data at index 
char* front(SLList* List);
char* itoa(int num, char* str, int base); //converts from integer to string
void reverse(char str[], int length); //utility function for itoa

char* front(SLList* List) {
    /*
    * Get the data at the head of the list
    */ 
    return List->head->data;
}


char* getAt(SLList* List, const int index) {
    return (traverse(List, index)->data);
}

void init(SLList* List) {
    /*
    *   initialize size to 0 and head to NULL
    */
   List->size = 0;
   List->head = NULL;
}

void printlist(SLList* List) {
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

Node* traverse(SLList* List,const int index) {
    /*
    * give an index N, traverse() traverse the list until N and return pointer to N-1
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

void insert(SLList* List, int index,const char* data) {
    /*
    * insert a node with data at index
    * O(n)
    */

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->data,data);

    
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else if(index == 0) { //case 2: front insertion
        new_node->next = List->head;
        List->head = new_node;
    } 
    else { //case 3: Non empty list with insert at middle
        Node* prev = traverse(List, index);
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}


void pushfront(SLList* List,const char* data) {
    /*
    * insert node at the front of the list
    */
   insert(List, 0, data);
} 

void pushback(SLList* List,const char* data) {
    /*
    * insert node at the end of the list
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


void suppress(SLList* List,const int index) {
    /*
    * suppress() deletes node at index
    * O(n)
    */ 

    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n");
        return;
    }

    //case 2: invalid index
    if(index < 0 || index >= List->size) {
        printf("invalid index");
        return;
    }

    Node* to_del;
    
    if(index == 0) { //case 3: deleting head
       to_del = List->head;
       List->head = (List->head)->next;

    } else {  //case 4: deleting any node that is not head
        Node* prev = traverse(List, index - 1);
        to_del = prev->next;
        prev->next = to_del->next;

    }
    
    free(to_del);
    --List->size;
}

void popfront(SLList* List) {
    /*
    * delete node at the back of the list
    */
    suppress(List,0);
}  
void popback(SLList* List) {
    /*
    * delete node at the front of the list
    */
    suppress(List, List->size - 1);
}  

char* itoa(int num, char* str, int base) { 
    //IMPLEMENTATION FROM GEEKSFORGEEKS
    int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 

void reverse(char str[], int length) { 
    //IMPLEMENTATION OF ITOA FROM GEEKSFORGEEKS
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        char tmp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = tmp;
        start++; 
        end--; 
    } 
} 

#endif