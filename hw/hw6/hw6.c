/*

  Author: Josias Moukpe 
  Email: jmoukpe2016@my.fit.edu
  Course: cse2010
  Section: 14b
  Description: graph to manage 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"
#include "graph.h"
// #include "query.h"

int main(int argc, char** argv) 
{

  FILE* factions = fopen(argv[1], "r"); // pointer to query files
  FILE* ffriends = fopen(argv[2], "r"); // pointer data query files

  
  if(factions == NULL ) 
  { // exits with failure if program fails to open data file
    printf("\nError: failed to open actions file.\n");
    exit(EXIT_FAILURE);
  }

  if(ffriends == NULL ) 
  { // exits with failure if program fails to open data file
    printf("\nError: failed to open fiends file.\n");
    exit(EXIT_FAILURE);
  }

  // Reading file inputs
  size_t len = 0; // keeps track of the length of the lines
  char* input_line = NULL;  // the input line charracter array  
  SLList* action = NULL; 
  SLList* friendship = NULL;
  uint number_of_lines = getline(&input_line, &len, ffriends); // reading the first line 

  // loop while not the end of the input file
  while(getline(&input_line, &len, ffriends) != EOF) 
  {
    friendship = parseWords(input_line); // converts input line into sllist of words
    printlist(friendship);
    printf("\n");
    // processQuery(logs, queries); // process the sllist of words in cmds
  }

  // loop while not the end of the input file
  while(getline(&input_line, &len, factions) != EOF) 
  {
    action = parseWords(input_line); // converts input line into sllist of words
    printlist(action);
    printf("\n");
    // processQuery(logs, queries); // process the sllist of words in cmds
  }
  
  // destroySList(logs);
  fclose(factions);
  fclose(ffriends);
  return EXIT_SUCCESS;
  
}

