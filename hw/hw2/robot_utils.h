#ifndef ROBOT_UTILS
#define ROBOT_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "SLinkedList.h"

typedef unsigned int uint;

typedef struct
{
    /* data */
    char* loc_name[128];
    uint loc_X;
    uint loc_Y;
    bool is_visited;

} location;


location* initLoc(uint x, uint y, bool is_visited); //location constructor
SLList* parseWords(char* line); //parse the words in line into a list

location* initLoc(uint x, uint y, bool is_visited) {
    /*
    *   Location constructor
    */
    location* loc = (location*)malloc(sizeof(location));
    loc->loc_X = x;
    loc->loc_Y = y;
    is_visited = false;
    return loc;
}

SLList* parseWords(char* line) {
    /*
    * Parses the input line for relevant commands
    */ 
    SLList* tmp = (SLList*)malloc(sizeof(SLList)); //command created with be used by then freed by parseCmd()
    init(tmp);

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

double distance(uint x1, uint x2, uint y1, uint y2) {
    /*
    * Given 
    */

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

#endif //ROBOT_UTILS