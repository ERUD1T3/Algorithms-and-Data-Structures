#ifndef ROBOT_UTILS
#define ROBOT_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "SLinkedList.h"
//#include "stack.h"
//#include "queue.h"

typedef unsigned int uint;

typedef struct
{
    /* data */
    char loc_name[128];
    uint loc_X;
    uint loc_Y;
    bool is_visited;

} location;


location* initLoc(char* loc_name, uint x, uint y, bool is_visited); //location constructor
SLList* parseWords(char* line); //parse the words in line into a list
int minPathFinder(uint rem_dest, SLList* visited, SLList* unvisited); //recursively find the path from and to start station
location* getLocation(SLList* cmd); //Creates a location struct from the command
location* str2loc(char* str);
char* loc2str(location* loc);





int minPathFinder(uint rem_dest, SLList* visited, SLList* unvisited) {
    /*
    * recursively find the path from and to the start station
    */
   for(uint i = 0; i < unvisited->size; ++i) {
       //popfront(unvisited)
   }
}


location* initLoc(char* loc_name, uint x, uint y, bool is_visited) {
    /*
    *   Location constructor
    */
    location* loc = (location*)malloc(sizeof(location));
    strcpy(loc->loc_name, loc_name);
    loc->loc_X = x;
    loc->loc_Y = y;
    is_visited = false;
    return loc;
}

SLList* parseWords(char* line) {
    /*
    * Parses the input line for relevant commands
    */ 
    SLList* tmp = initList(); //command created with be used by then freed by parseCmd()

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

location* getLocation(SLList* cmd) { 
    /*
    *  Creates a location struct from the command
    */
    return initLoc(
        getAt(cmd,0),
        atoi(getAt(cmd,1)), 
        atoi(getAt(cmd,2)),
        false);
}

double distance(uint x1, uint x2, uint y1, uint y2) {
    /*
    * Computes the staightline distance between two set of coordinates
    */

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


char* loc2str(location* loc) {
    char str[MAX_STR_SIZE];
    char buffer[10];
    
    //strcpy(str, "\0");
    strcat(str, loc->loc_name);
    strcat(str, " ");
    itoa(loc->loc_X, buffer, 10);
    strcat(str, buffer);
    strcat(str, " ");
    strcpy(buffer, "\0");
    itoa(loc->loc_Y, buffer, 10);
    strcat(str, buffer);
    strcat(str, " ");
    strcpy(buffer, "\0");

    return str;
}

location* str2loc(char* str) {
    SLList* tmp = parseWords(str);

    return initLoc(
        getAt(tmp, 0), 
        atoi(getAt(tmp, 1)), 
        atoi(getAt(tmp, 2)),
        false);
}


#endif //ROBOT_UTILS