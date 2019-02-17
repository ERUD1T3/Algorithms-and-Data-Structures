/*

  Author: Josias Moukpe
  Email: jmoukpe2016@my.fit.edu
  Course: cse2010
  Section: 14
  Description: Tree Taxonmy

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "TTree.h"
#include "SLinkedList.h"

/*
  Description of the function, parameter, and return value (if any)
 */

int main(int argc, char** argv)
{
  //keeps track of the length of the lines
  size_t len = 0;          
  //the input line charracter array                   
  char* input_line = NULL; 

  char* datafile = argv[1];
  char* queryfile = argv[2];

   //pointer the input file
  FILE* fdata = fopen(datafile, "r");    
  //FILE* fquery = fopen(queryfile, "r");   

  /*
    L36-41: exits program if file ptr is null ie no file was found
   */
  if(fdata == NULL) {
    printf("\nError: failed to open data file.\n");
    exit(EXIT_FAILURE);
  }

  /*
  if(fquery == NULL) {
    printf("\nError: failed to open query file.\n");
    exit(EXIT_FAILURE);
  }
  */
  /*
  * Reading the data file and building the data tree
  */ 
  while(getline(&input_line, &len, fdata) != EOF) {
    //printf("%s",input_line);
    SLList* datalist = parseWords(input_line);
    //printf(" input data: ");
    _printlist(datalist);
    //printf("\n");
  }

  /*
  * Reading query file and executing the queries
  */ 
 /*

  while(getline(&input_line, &len, fquery) != EOF) {
    //printf("%s",input_line);
    SLList* querylist = parseWords(input_line);
    printf("\n input query: ");
    _printlist(querylist);
    //printf("\n");
  }
*/



  



  



  /*
    description of each "block" (about 5 lines of instructions)
  */
  
  fclose(fdata);
  //fclose(fquery);
  return EXIT_SUCCESS;
}

