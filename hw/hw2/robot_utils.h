#ifndef ROBOT_UTILS
#define ROBOT_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "SLinkedList.h"
#include "LocList.h"

/*
typedef unsigned int uint;

typedef struct
{
    char loc_name[128];
    uint loc_X;
    uint loc_Y;
    bool is_visited;

} location;
*/

location* initLoc(char* loc_name, uint x, uint y, bool is_visited); //location constructor
SLList* parseWords(char* line); //parse the words in line into a list
void minPathFinder(double* min_dist, location* path[], uint size, uint rem_dest, LocList* visited, LocList* unvisited); //recursively find the path from and to start station
location* getLocation(SLList* cmd); //Creates a location struct from the command
double distance(location* loc1, location* loc2); //computes the distance between two locations
double path_length(location* path[], uint size, bool to_print); //computes the overall path length


///UNDER CONSTRUCTION///////////////////////////////////////////////
void minPathFinder(double* min_dist, location* path[], uint size, uint rem_dest, LocList* visited, LocList* unvisited) {
    /*
    * recursively find the path from and to the start station
    */
   
   for(uint i = 0; i < unvisited->size; ++i) {
       location* curr_loc = popfront(unvisited);
       pushback(visited, curr_loc);

       if(rem_dest == 1) {
           for(uint i = 0; i < visited->size; ++i) 
               path[i+1] = getAt(visited, i);
            //path[1+visited->size] = str2loc(getAt(unvisited, 0));
           double tmp = path_length(path, size, false);
           if(tmp < *min_dist) {
               *min_dist = tmp;
               printf("found a smaller path\n");
           }
           else {
               printf("didn't find a smaller path\n");
           }
       } 
       else {
        minPathFinder(min_dist, path, size, rem_dest - 1, visited, unvisited);
       }
       pushfront(unvisited, curr_loc);
       popback(visited);

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
        _pushback(tmp, word_token);
        word_token = strtok(NULL, delim);
    }

    return tmp; 
} 

location* getLocation(SLList* cmd) { 
    /*
    *  Creates a location struct from the command
    */
    return initLoc(
        _getAt(cmd,0),
        atoi(_getAt(cmd,1)), 
        atoi(_getAt(cmd,2)),
        false);
}

double distance(location* loc1, location* loc2) {
    /*
    * Computes the staightline distance between two set of coordinates
    */
    return sqrt(
        pow(((double)loc2->loc_Y - loc1->loc_Y), 2) + 
        pow(((double)loc2->loc_X - loc1->loc_X), 2)
        );
}

double path_length(location* path[], uint size, bool to_print) {
    /*
        computes a path length
    */
    double total_len = 0;
    if(to_print) printf("%s %d %d %.2lf\n", path[0]->loc_name, path[0]->loc_X, path[0]->loc_Y, 0.00);
    for(uint i = 0, j = 1; j < size; ++i, ++j) {
        double dist = distance(path[i], path[j]);
        if(to_print) printf("%s %d %d %.2lf\n", path[j]->loc_name, path[j]->loc_X, path[j]->loc_Y, dist);
        total_len += dist;
    }
    return total_len;
}

#endif //ROBOT_UTILS