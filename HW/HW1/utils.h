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
 
typedef unsigned int  uint;

typedef struct {
    char worker[256];
    char customer[256];
    uint order_time;
    uint n_books;
    uint n_electronics;
    int end_time;
    //Bundle order_bundle;
} Order;

const char* cmds[MAX_CMD] = { //List of commands to expect from input file
    "CustomerOrder", 
    "PrintAvailableWorkerList", 
    "PrintWorkerAssignmentList", 
    "PrintMaxFulfillmentTime" 
    };

const char* workers[MAX_WORKERS] = { "Alice", "Bob", "Carol", "David", "Emily" };
const char* categories[MAX_CAT] = { "Electronics", "Books" };


SLList* parseWords(char* line); //obtain words from input lines and insert them into a list
void printAvailWorker(uint time, SLList* avail_workers); //print a list of the currently available workers
void printWorkerAssign(uint time, SLList* assignments); //print a list of workers with their assigned customer
void printMaxFulfilTime(uint time); //print the time it would take for all orders to be processed
void checkOrderCompletion(uint time); //print the list of all orderes complete int the given time
uint computeEndTime(Order* order); //compute the end time of an order
void parseCmd(
    SLList* cmd_line, 
    SLList* avail_workers, 
    SLList* customers, 
    SLList* assignment,
    Order** prev_order
    );  //assign relevant words to a function
Order* customerOrder(
    uint start_time, 
    char* cost_name, 
    SLList* avail_worker, 
    uint n_books,
    uint n_tronics,
    Order** prev_order,
    SLList* assignments
    ); //function to handle the costumer order
void initOrder(
    Order* order,
    char* customer,
    char* worker,
    uint order_time,
    uint n_books,
    uint n_electronics,
    int end_time 
    ); //initializes an order with the inputted parameters

/********************************************
* IMPLEMENTATION OF THE FUNCTIONS IN UTILS_H
*********************************************/

void initOrder(Order* order, char* customer, char* worker, uint order_time, uint n_books, uint n_electronics, int end_time) {
        strcpy(order->worker, worker);
        strcpy(order->customer, customer);
        order->order_time = order_time;
        order->n_books = n_books;
        order->n_electronics = n_electronics;
        order->end_time = end_time;
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

void parseCmd(SLList* cmd, SLList* avail_workers, SLList* customers, SLList* assignments, Order** prev_order) {

    //case costumerOrder
    char* tmp = (char*)malloc(1024*sizeof(char));

    if(!strcmp(getAt(cmd, 0), cmds[0])) {
        
        *prev_order = customerOrder(
            atoi(getAt(cmd, 1)), 
            getAt(cmd, 2), 
            avail_workers, 
            atoi(getAt(cmd, 3)), 
            atoi(getAt(cmd, 4)),
            prev_order, 
            assignments
            );
        
        //adding a new assignment to the assignment list
        if((*prev_order)->end_time != -1) {
            strcpy(tmp, (*prev_order)->worker); 
            strcat(tmp, ":");
            strcat(tmp, (*prev_order)->customer);
            pushback(assignments, tmp);
        }  
    } 

    //case printAvailWorker
    else if(!strcmp(getAt(cmd, 0), cmds[1])) {
        printAvailWorker(atoi(getAt(cmd, 1)), avail_workers);
    } 

    //case printWorkerAssign
    else if(!strcmp(getAt(cmd, 0), cmds[2])) {
        printWorkerAssign(atoi(getAt(cmd, 1)), assignments);
    }

    //case PrintMaxFulfillmentTime
    else if(!strcmp(getAt(cmd, 0), cmds[3])) {
        printMaxFulfilTime(atoi(getAt(cmd, 1)));
    } 
    //case of invalid command in the program
    else {
        printf("Invalid Command\n");
    }
    free(cmd);
}

/****************UNDER CONSTRUCTION**********************************************/
Order* customerOrder(uint start_time, 
                    char* cost_name, 
                    SLList* avail_workers, 
                    uint n_books, 
                    uint n_tronics, 
                    Order** prev_order,
                    SLList* assignments) {
    
    //invalid order 
    if((n_books <= 0  && n_tronics <= 0) || (n_books + n_tronics) > 10) {
        printf("Invalid Order, \nNo or Too many book(s) and eletronic(s) ordered\n");
        return NULL;
    }
    
    Order* curr_order; //creating order structure

    
    if(n_books != 0 && n_tronics != 0) {
        curr_order = (Order*)malloc(sizeof(Order));
        initOrder(curr_order, cost_name, front(avail_workers), start_time, n_books, n_tronics, 0);
        printf("WorkerAssignment %d %s %s\n", curr_order->order_time, curr_order->worker, curr_order->customer);
        popfront(avail_workers);
        return curr_order;
    }
    
    
    //printf("previous book: %d and eletronics: %d\n", (*prev_order)->n_books, (*prev_order)->n_electronics);
    //Electronics bundle
    if(n_books == 0) {
        if( prev_order != NULL && 
            (*prev_order)->n_books == 0 && 
            ((*prev_order)->n_electronics + n_tronics) <= 10) {
            //concatenate cost_name for bundles
            //order->order_bundle
            curr_order = *prev_order;
            curr_order->n_electronics += n_tronics;
            strcat(curr_order->customer, " ");
            strcat(curr_order->customer, cost_name);
            curr_order->end_time = -1;
            //not sure if start time changes
            //not sure if end time should change
            //return curr_order;
        } 
        else {
            curr_order = (Order*)malloc(sizeof(Order));
            initOrder(curr_order, cost_name, front(avail_workers), start_time, n_books, n_tronics, 0);
            //printf("WorkerAssignment %d %s %s\n", (*prev_order)->order_time, (*prev_order)->worker, (*prev_order)->customer);
            //printf("WorkerAssignment %d %s %s\n", curr_order->order_time, curr_order->worker, curr_order->customer);
            popfront(avail_workers); 
        }
    } 

    //Book bundle
    else if(n_tronics == 0) {
        if( prev_order != NULL &&
            (*prev_order)->n_electronics == 0 && 
            ((*prev_order)->n_books + n_books) <= 10) {
            //concatenate cost_name for bundles
            //order->order_bundle
            curr_order = *prev_order;
            curr_order->n_books += n_books;
            strcat(curr_order->customer, " ");
            strcat(curr_order->customer, cost_name);
            curr_order->end_time = -1;
            //not sure if start time changes
            //not sure if end time should change
            //return curr_order;
        }
        else {
            curr_order = (Order*)malloc(sizeof(Order));
            initOrder(curr_order, cost_name, front(avail_workers), start_time, n_books, n_tronics, 0);
            //printf("WorkerAssignment %d %s %s\n", (*prev_order)->order_time, (*prev_order)->worker, (*prev_order)->customer);
            //printf("WorkerAssignment %d %s %s\n", curr_order->order_time, curr_order->worker, curr_order->customer);
            popfront(avail_workers); 
        }
    } 
    
    //case order is not bundled
    else {
        //stop the bundle
        printf("ORDER IS NOT BUNDLED\n");
        curr_order = (Order*)malloc(sizeof(Order));
        initOrder(curr_order, cost_name, front(avail_workers), start_time, n_books, n_tronics, computeEndTime(curr_order));
        //printf("WorkerAssignment %d %s %s\n", (*prev_order)->order_time, (*prev_order)->worker, (*prev_order)->customer);
        printf("WorkerAssignment %d %s %s\n", curr_order->order_time, curr_order->worker, curr_order->customer);
        popfront(avail_workers); 
    }
    

    return curr_order;
    
}

void printAvailWorker(uint time, SLList* avail_workers) {
    /*
    * print a list of the currently available workers
    * check for every order for whether the completion time > order->end_time;
    */
    printf("AvailableWorkerList ");
    printlist(avail_workers);
} 

void printWorkerAssign(uint time, SLList* assignments) {
    /*
     * print a list of workers with their assigned customer
     * 
    */
    printf("WorkerAssignmentList ");
    printlist(assignments);
}

void printMaxFulfilTime(uint time) {
    /*
    *print the time it would take for all orders to be processed
    */
}

/**************************************
 * STILL BRAINSTORMING
 **************************************/ 
uint computeEndTime(Order* order) {
    /*
    * Computes the end time of the order completion
    */
    return order->n_electronics + 
            TRAVEL_T * ((order->n_electronics == 0)?1:0) +
            order->n_books + 
            TRAVEL_T * ((order->n_books == 0)?1:0);
}

void checkOrderCompletion(uint time) {
    /*
    * Pints a list of completed orders
    */


}



#endif