/*

  Author: Josias Moukpe 
  Email: jmoukpe2016@my.fit.edu
  Course: cse2010
  Section: 14b
  Description: skiplist to log and manage user activities



 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"
#include "skipList.h"
// #include "query.h"


/*
  Description for each function, parameter, and return value (if any)
 */
int main(int argc, char** argv)
{
  /*
    description of declared variables
   */


  /*
    description for each "block" (about 5 lines of instructions)
   */
  
  FILE* fp = fopen(argv[1], "r"); // pointer the input data and query files
  
  if(fp == NULL) { // exits with failure if program fails to open data file
    printf("\nError: failed to open input file.\n");
    exit(EXIT_FAILURE);
  }

  // Reading file inputs
  size_t len = 0; // keeps track of the length of the lines
  char* input_line = NULL;  // the input line charracter array  
  SLList* cmds = NULL;
 
  while(getline(&input_line, &len, fp) != EOF) {
    // printf("%s\n", input_line);
    cmds = parseWords(input_line);
    printlist(cmds);
    printf("\n");
    // processQuery(bids, cmds);
  }
  
  fclose(fp);
  return EXIT_SUCCESS;
}



// put(skiplist, ...) 
// uses getRandHeight()


