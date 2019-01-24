/*

  Author: Josias Moukpe
  Email: jmoukpe2016@my.fit.edu
  Course: Algorithms and Data Structures
  Section: 14
  Description: Program manages orders in a store. Programs is devided into 3 files
  hw1.c, utils.h, and SLinkedList.h

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SLinkedList.h"
#include "utils.h"

/*
  Description for each function, parameter, and return value (if any)
*/

int main(int argc, char* argv[])
{
  /*
    description of declared variables
  */

  char* infile = argv[1]; //taking file name in as second argument
  //char* outfile = (strcmp(argv[2], ""))?argv[2]:"input.txt";
  //char*  infile = "input.txt";
  //printf("\nstarting to read input\n");

  FILE* fp = fopen(infile, "r");
  FILE* fp_next = fopen(infile, "r");

  if(fp == NULL || fp_next == NULL) {
      printf("\nError: failed to open file.\n");
      exit(EXIT_FAILURE);
  }

  //printf("\ninitializing the program\n");

  char* input_line = NULL; //input line from file
  char* next_line = NULL; //input to the next line in file 
  //char* next_line = NULL;
  size_t len = 0, next_len = 0;
  SLList* curr_cmd; //list of commands from lines
  SLList* next_cmd;
  SLList* avail_workers = (SLList*)malloc(sizeof(SLList));
  SLList* customer_orders = (SLList*)malloc(sizeof(SLList));
  SLList* assignments = (SLList*)malloc(sizeof(SLList));
  Order* prev_order = NULL;

  init(avail_workers);
  init(customer_orders);
  init(assignments);

  //setting all workers to available at the start of the program
  for(uint i = 0; i < MAX_WORKERS; ++i) pushback(avail_workers, workers[i]); 

  getline(&next_line, &next_len, fp_next); //setting up the look ahead on the following night
  //getline(&input_line, &len, fp) != EOF



  while(getline(&input_line, &len, fp) != EOF) {


    getline(&next_line, &next_len, fp_next);
    printf("%s", input_line);
    //printf("next: %s", next_line);

    curr_cmd = parseWords(input_line);
    next_cmd = parseWords(next_line);
    
    //printf("printing the list of commands\n");
   
    //parseCmd(cmd_line, avail_workers, customer_orders, assignments, &prev_order); //attempt at implementation based on previous
    parseCmd(curr_cmd, avail_workers, customer_orders, assignments, next_cmd, &prev_order);  //implementation based on looking at next commands

  }

  printf("\n");
  free(avail_workers);
  free(assignments);
  free(customer_orders);
  fclose(fp);
  return EXIT_SUCCESS;
}
