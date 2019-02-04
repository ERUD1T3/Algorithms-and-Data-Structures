/*

  Author: Josias Moukpe
  Email: jmoukpe2016@my.fit.edu 
  Course: cse2010
  Section: 14
  Description: Algorithm to recursively find the shortest path in a store




 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "robot_utils.h"

/*
  Description of the function, parameter, and return value (if any)
 */

int main(int argc, char** argv)
{

  /*
    description of declared variables
   */
  size_t len = 0;

  /*
    description of declared variables
   */
  char* input_line = NULL;

  /*
    taking file name in as second argument
   */
  char* infile = argv[1]; 

  /*
    taking file name in as second argument
   */
  FILE* fp = fopen(infile, "r");

  /*
    store the number destination the map 
  */
  uint n_dest = 0;


  /*
    description of each "block" (about 5 lines of instructions)
   */
  if(fp == NULL) {
      printf("\nError: failed to open file.\n");
      exit(EXIT_FAILURE);
  }

  getline(&input_line, &len, fp);
  n_dest = 1 + atoi(input_line); //since robot has to return to starting position
  printf("number of destionation is : %d\n", n_dest);

  location* arrloc[n_dest];

  for(uint i = 0; i < n_dest - 1; ++i) {
    getline(&input_line, &len, fp);
    arrloc[i] = getLocation(parseWords(input_line));
  }
  arrloc[n_dest - 1] = arrloc[0];

  //for(uint i = 0; i < n_dest; ++i) printf("%s\n", arrloc[i]->loc_name);
  printf("Total path length: %.2lf\n", path_length(arrloc, n_dest, true));
  /*
    description of each "block" (about 5 lines of instructions)
   */

  SLList* visited = initList();
  SLList* unvisited = initList();
  for(uint i = 1; i < n_dest - 1; ++i) pushback(unvisited, loc2str(arrloc[i]));
  double min_dist = path_length(arrloc, n_dest, false);
  minPathFinder(&min_dist, arrloc, n_dest - 2, visited, unvisited);

  fclose(fp);
  return EXIT_SUCCESS;
}
