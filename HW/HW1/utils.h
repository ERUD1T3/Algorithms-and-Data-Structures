/*
* Josias Moukpe
* Header file containing utility functions for HW1
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SLinkedList.h"

#define MAX_ORDER  10 //at most 10 items per bundle
#define PICK_T 1 //time to pick item within a category
#define TRAVEL_T 5  //time it takes to travel from one category to the next
#define MAX_WORKERS 5 //total number of workers
#define MAX_CAT 2 //total number of categories
#define MAX_CMD 4 //total number of commands to handle
 
//typedef unsigned int  int;

typedef struct {
    char worker[256];
    char customer[256];
    int order_time;
    int n_books;
    int n_electronics;
    int fulfil_time;
    //Bundle order_bundle;
} Order;

const char* workers[MAX_WORKERS] = { "Alice", "Bob", "Carol", "David", "Emily" };
//const char* categories[MAX_CAT] = { "Electronics", "Books" };

void printOrder(Order* order); //print an order
char* order2string(Order* order); //convert order into list for inserting in list
Order* string2order(char* str); //convert a string back to an order
SLList* parseWords(char* line); //obtain words from input lines and insert them into a list
void printAvailWorker(int time, SLList* avail_workers); //print a list of the currently available workers
void printWorkerAssign(int time, SLList* assignments); //print a list of workers with their assigned customer
void printMaxFulfilTime(int curr_time, SLList* order_list); //print the time it would take for all orders to be processed
void checkOrderCompletion(int time, SLList* customer_orders); //print the list of all orderes complete int the given time
int EstimatedTime(int n_books, int n_electronics); //compute the end time of an order
void parseCmd(
    SLList* cmd_line, 
    SLList* avail_workers, 
    SLList* customer_orders, 
    SLList* assignment,
    SLList* next_cmd,
    Order** prev_order
    );  //assign relevant words to a function
Order* customerOrder(
    int start_time, 
    char* cost_name, 
    SLList* avail_worker, 
    int n_books,
    int n_tronics,
    Order** prev_order,
    SLList* next_cmd
    ); //function to handle the costumer order
void initOrder(
    Order* order,
    char* customer,
    char* worker,
    int order_time,
    int n_books,
    int n_electronics,
    int fulfil_time 
    ); //initializes an order with the inputted parameters

/********************************************
* IMPLEMENTATION OF THE FUNCTIONS IN UTILS_H
*********************************************/

void initOrder(Order* order, char* worker, char* customer, int order_time, int n_books, int n_electronics, int fulfil_time) {
        strcpy(order->worker, worker);
        strcpy(order->customer, customer);
        order->order_time = order_time;
        order->n_books = n_books;
        order->n_electronics = n_electronics;
        order->fulfil_time = fulfil_time;
}

SLList* parseWords(char* line) {
    /*
    * Parses the input line for relevant commands
    */ 
    SLList* tmp = (SLList*)malloc(sizeof(SLList)); //command created with be used by then freed by parseCmd()
    char* word_token;
    char* delim = " \n";

    /* get the first token */
    word_token = strtok(line, delim);

    /* walk through other tokens */
    while(word_token != NULL) {
        //printf( " %s\n", word_token);
        pushback(tmp, word_token);
        word_token = strtok(NULL, delim);
    }

    return tmp; 
} 

void parseCmd(SLList* cmd, 
        SLList* avail_workers, 
        SLList* customer_orders, 
        SLList* assignments, 
        SLList* next_cmd, 
        Order** prev_order) {

    //case costumerOrder
    char* tmp = (char*)malloc(1024*sizeof(char));
    
    checkOrderCompletion(atoi(getAt(cmd, 1)), customer_orders);

    if(!strcmp(getAt(cmd, 0), "CustomerOrder")) {
        
        *prev_order = customerOrder(
            atoi(getAt(cmd, 1)), 
            getAt(cmd, 2), 
            avail_workers, 
            atoi(getAt(cmd, 3)), 
            atoi(getAt(cmd, 4)),
            prev_order, 
            next_cmd
            );
        //adding a new assignment to the assignment list
        if((*prev_order)->fulfil_time != -1) {
            strcpy(tmp, (*prev_order)->worker); 
            strcat(tmp, ":");
            strcat(tmp, (*prev_order)->customer);
            pushback(assignments, tmp);
        }  
        pushback(customer_orders, order2string(*prev_order));
    } 

    //case printAvailWorker
    else if(!strcmp(getAt(cmd, 0), "PrintAvailableWorkerList")) {
        printAvailWorker(atoi(getAt(cmd, 1)), avail_workers);
    } 

    //case printWorkerAssign
    else if(!strcmp(getAt(cmd, 0), "PrintWorkerAssignmentList")) {
        printWorkerAssign(atoi(getAt(cmd, 1)), assignments);
    }

    //case PrintMaxFulfillmentTime
    else if(!strcmp(getAt(cmd, 0), "PrintMaxFulfillmentTime")) {
        //Order* bundle[8];
        //printf("******************************\n");
        //printlist(customer_orders);
        //printf("******************************\n");
        printMaxFulfilTime(atoi(getAt(cmd, 1)), customer_orders);
    } 
    //case of invalid command in the program
    else {
        printf("Invalid Command\n");
    }
    free(cmd);
}

/****************UNDER CONSTRUCTION**********************************************/
Order* customerOrder(int start_time, 
                    char* cost_name, 
                    SLList* avail_workers, 
                    int n_books, 
                    int n_tronics, 
                    Order** prev_order,
                    SLList* next_cmd) {
    
    //invalid order 
    if((n_books <= 0  && n_tronics <= 0) || (n_books + n_tronics) > 10) {
        printf("Invalid Order, \nNo or Too many book(s) and eletronic(s) ordered\n");
        return NULL;
    }
    
    if(avail_workers->size == 0) {
        printf("No more workers available\n");
        return NULL;
    }
    
    Order* curr_order; //creating order structure
    bool isNewOrderToProcess = true;

    //case: Electronics bundle
    if(n_books == 0) {
       
        if(prev_order == NULL) {
            isNewOrderToProcess = true;
        }
        else if(strcmp(getAt(next_cmd, 0), "CustomerOrder") || //true if strings are not the same
                atoi(getAt(next_cmd, 3)) != 0 || //number of books is at 3rd position
                ((*prev_order)->n_electronics + n_tronics) > 10 || //eletronics bundle exceeded limit
                (start_time - (*prev_order)->order_time) > 5) { 
                    isNewOrderToProcess = true;
        } 
        else {
            curr_order = *prev_order;
            curr_order->n_electronics += n_tronics;
            strcat(curr_order->customer, " ");
            strcat(curr_order->customer, cost_name);
            curr_order->order_time = start_time;
            curr_order->fulfil_time = -1;
            isNewOrderToProcess = false;
        }
        
    } 

    //case: Book bundle
    else if(n_tronics == 0) {
       
        if(prev_order == NULL) {
            isNewOrderToProcess = true;
        }
        else if(strcmp(getAt(next_cmd, 0), "CustomerOrder") || //true if strings are not the same
                atoi(getAt(next_cmd, 4)) != 0 || //number of Electronics is at 4th position
                ((*prev_order)->n_books + n_books) > 10 || //book bundle exceeded limit
                (start_time - (*prev_order)->order_time) > 5) { 
                    isNewOrderToProcess = true;
        } 
        else {
            curr_order = *prev_order;
            curr_order->n_books += n_books;
            strcat(curr_order->customer, " ");
            strcat(curr_order->customer, cost_name);
            curr_order->order_time = start_time;
            curr_order->fulfil_time = -1;
            isNewOrderToProcess = false;
        }
        
    } 
    
    //case: order is not bundled
    else {
        isNewOrderToProcess = true;
    }
    
    if(isNewOrderToProcess) {
        curr_order = (Order*)malloc(sizeof(Order));
        initOrder(curr_order, 
            front(avail_workers), 
            cost_name, 
            start_time, 
            n_books, 
            n_tronics, 
            EstimatedTime(n_books, n_tronics));
        printf("WorkerAssignment %d %s %s\n", curr_order->order_time, curr_order->worker, curr_order->customer);
        popfront(avail_workers);    
    }

    return curr_order;
      
}

void printAvailWorker(int time, SLList* avail_workers) {
    /*
    * print a list of the currently available workers
    * check for every order for whether the completion time > order->fulfil_time;
    */
    printf("AvailableWorkerList ");
    printlist(avail_workers);
} 

void printWorkerAssign(int time, SLList* assignments) {
    /*
     * print a list of workers with their assigned customer
     * 
    */
    printf("WorkerAssignmentList ");
    printlist(assignments);
}

void printMaxFulfilTime(int curr_time, SLList* order_list) {
    /*
    *print the time it would take for all orders to be processed
    */
   int latest = string2order(getAt(order_list, 0))->fulfil_time;
    //printf("latest: %d\n", latest);
   for(int i = 1; i < order_list->size; ++i) {
       int current = string2order(getAt(order_list, i))->fulfil_time;
       //printf("size: %d, i: %d\n", order_list->size, i);
       if(current > latest) {
           latest = current;
       }
   }
   printf("\nMaxFulfillmentTime %d", latest);
}

int EstimatedTime(int n_books, int n_electronics) {
    /*
    * Computes the end time of the order completion
    */
    int ETA = 0;
    if(n_electronics != 0) {
        ETA += (TRAVEL_T + PICK_T*(n_electronics));
    }

    if(n_books != 0) {
        ETA += (TRAVEL_T + PICK_T*(n_books));
    }
    return  ETA;
}

char* order2string(Order* order) {
    char* order_str = (char*)malloc(MAX_STRING_SIZE*sizeof(char));
    char buffer[8];
    strcpy(order_str, "\0");
    strcat(order_str, order->worker);
    strcat(order_str, " ");
    strcat(order_str, order->customer);
    strcat(order_str, " ");
    itoa(order->order_time, buffer, 10);
    strcat(order_str, buffer);
    strcat(order_str, " ");
    strcpy(buffer, "\0");
    itoa(order->n_books, buffer, 10);
    strcat(order_str, buffer);
    strcat(order_str, " ");
    strcpy(buffer, "\0");
    itoa(order->n_electronics, buffer, 10);
    strcat(order_str, buffer);
    strcat(order_str, " ");
    strcpy(buffer, "\0");
    itoa(order->fulfil_time, buffer, 10);
    strcat(order_str, buffer);
    strcat(order_str, " ");
    //strcpy(buffer, "");

    return order_str;
}

Order* string2order(char* str) {
    Order* order = (Order*)malloc(sizeof(Order));
    SLList* tmp = parseWords(str);
    
    //printf("\ntmp: ");
    //printlist(tmp);
    //printf("\n");

    initOrder(order, 
        getAt(tmp, 0), 
        getAt(tmp, 1),
        atoi(getAt(tmp, 2)),
        atoi(getAt(tmp, 3)),
        atoi(getAt(tmp, 4)),
        atoi(getAt(tmp, 5))
        );

    //printf("************************\n");
    //printOrder(order);
    //printf("************************\n");
    return order;
}

/**************************************
 * STILL BRAINSTORMING
 **************************************/ 
void checkOrderCompletion(int curr_time, SLList* customer_orders) {
    /*
    * Pints a list of completed orders
    */
   /*
   int bundle_size = 0;
   //if(curr_time == ) 
   for(int i = 0; i < bundle_size; ++i) {
    printf("OrderCompletion %d %s", bundle[i]->fulfil_time, bundle[i]->customer);
   }
   */
}

void printOrder(Order* order) {
    printf("worker: %s customer: %s start_time: %d book: %d  Electronics: %d  fulfil_time: %d", 
    order->worker, order->customer, order->order_time, order->n_books, order->n_electronics, order->fulfil_time);
}


#endif