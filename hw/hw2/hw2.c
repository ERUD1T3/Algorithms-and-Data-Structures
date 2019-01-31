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
    description of each "block" (about 5 lines of instructions)
   */
  if(fp == NULL) {
      printf("\nError: failed to open file.\n");
      exit(EXIT_FAILURE);
  }

  while(getline(&input_line, &len, fp) != EOF) {

  }
  /*
    description of each "block" (about 5 lines of instructions)
   */
  return EXIT_SUCCESS;
}
