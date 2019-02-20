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
#include "TTree.h"
#include "Querying.h"


/*
  Description of the function, parameter, and return value (if any)
 */

int main(int argc, char** argv)
{
  
  size_t len = 0; //keeps track of the length of the lines
  char* input_line = NULL;  //the input line charracter array  

  char* datafile = argv[1];
  char* queryfile = argv[2];

   //pointer the input file
  FILE* fdata = fopen(datafile, "r");    
  FILE* fquery = fopen(queryfile, "r");   


  /*
    L36-41: exits program if file ptr is null ie no file was found
   */
  if(fdata == NULL || fquery == NULL) {
    printf("\nError: failed to open files.\n");
    exit(EXIT_FAILURE);
  }

  /*
  * Reading the data file and building the data tree
  */ 
  TNList* datalist = NULL;
  TNList* querylist = NULL;

  TTree* taxonomy = initTTree();

  uint counter = 0; 

  while(getline(&input_line, &len, fdata) != EOF) {
    
    //printf("%s",input_line);
    datalist = parseWords(input_line);
    //printf("input data: ");
    //printlist(datalist);
    
    //printf("about to build that tree!\n");
    buildTTree(taxonomy, datalist);
    //printf("done building tree!\n");
    //break;
    // if(counter > 1) break;
    // counter++;
  }

  printTTree(taxonomy);
  printf("\n");
  

  /*
  * Reading query file and executing the queries
  */ 
  while(getline(&input_line, &len, fquery) != EOF) {
    //printf("%s",input_line);
    querylist = parseWords(input_line);
    //printf("input query: ");
    printlist(querylist);
    processQuery(taxonomy, querylist);
    printf("\n");
  }


  /*
    garbage collection and clean up closing the files
  */

  destroyTTree(taxonomy);
  fclose(fdata);
  fclose(fquery);
  
  return EXIT_SUCCESS;
}


