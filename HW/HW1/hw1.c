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

  //printf("\nstarting to read input\n");

  FILE* fp = fopen(infile, "r");

  if(fp == NULL) {
      printf("\nError: failed to open file.\n");
      exit(EXIT_FAILURE);
  }

  //printf("\ninitializing the program\n");

  char* input_line = NULL; //input line from file
  //char* next_line = NULL;
  size_t len = 0;
  SLList* cmd_line; //list of commands from lines
  SLList* next_line;
  SLList* avail_workers = (SLList*)malloc(sizeof(SLList));
  SLList* customers = (SLList*)malloc(sizeof(SLList));
  SLList* assignments = (SLList*)malloc(sizeof(SLList));
  Order* prev_order = NULL;

  init(avail_workers);
  init(customers);
  init(assignments);

  //setting all workers to available at the start of the program
  for(uint i = 0; i < MAX_WORKERS; ++i) pushback(avail_workers, workers[i]); 
  
  //getline(&input_line, &len, fp) != EOF
  while(getline(&input_line, &len, fp) != EOF) {
    printf("%s", input_line);
    cmd_line = parseWords(input_line);
    //printf("printing the list of commands\n");
    /*
    printlist(cmds);
    printf("cmd first word: %s\n", getAt(cmds, 0));
    */
    parseCmd(cmd_line, avail_workers, customers, assignments, &prev_order);
    //parseCmd(cmd_line, avail_workers, customers, assignments, next_line);
    //cmd_line = next_line;
  }

  printf("\n");
  free(avail_workers);
  free(assignments);
  free(customers);
  fclose(fp);
  return EXIT_SUCCESS;
}
