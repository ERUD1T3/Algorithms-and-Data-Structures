#ifndef ROBOT_UTILS
#define ROBOT_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "SLinkedList.h" 
#include "LocList.h"

location* initLoc(char* loc_name, uint x, uint y); //location constructor
SLList* parseWords(char* line); //parse the words in line into a list
location* getLocation(SLList* cmd); //Creates a location struct from the command
double distance(location* loc1, location* loc2); //computes the distance between two locations
double path_length(LocList* path, bool to_print); //computes the minimum path
void pathFinder(double* min_dist, uint rem_dest, LocList* minpath, LocList* unvisited); //utilizes min path finder to output a path
void iterPathFinder(); //iterative implementation of the path finder
void pathShuffler( //recursively find the path from and to start station
    double* min_dist, //reference to minimum path length
    uint rem_dest, //remaining destinations to visit
    LocList* minpath, //reference to the minimum path list 
    LocList* visited, //reference to the list of visited locations
    LocList* unvisited, //reference to the list of unvisited locations
    location* start_station); //reference to the starting station location




void iterPathFinder() {

}

void pathFinder(double* min_dist, uint rem_dest, LocList* minpath, LocList* unvisited) {

    /*
    * Computes the minimum path by calling pathShuffler on unvisited without start station
    */

    LocList* reduced_unvisited = initLocList();
    LocList* visited = initLocList();

    for(uint i = 1; i < unvisited->size - 1; ++i) pushback(reduced_unvisited, getAt(unvisited, i));
    //printlist(reduced_unvisited);

    
    pathShuffler(min_dist, rem_dest - 2, minpath, visited, reduced_unvisited, getAt(unvisited, 0));
    
    destroy(reduced_unvisited);
    destroy(visited);
    
}

void pathShuffler(double* min_dist, uint rem_dest, LocList* minpath, LocList* visited, LocList* unvisited, location* start_station) {
    /*
    * recursively find the path with the minimum distance
    */
    
    // printf("Visited: ");
    // printlist(visited); printf("\n");
    // printf("unvisited: ");
    // printlist(unvisited); printf("\n");

    for(uint i = 0; i < unvisited->size; ++i) {
        location* curr_loc = popfront(unvisited);
        pushback(visited, curr_loc);

        if(rem_dest == 1) { //almost all destinations have been assigned

            pushfront(visited, start_station);
            pushback(visited, start_station);

            double curr_len = path_length(visited, false);

            if(curr_len < *min_dist) {
                *min_dist = curr_len;
                reset(minpath);
                

                //makes a call to initLocList()
                
                LocList* reversed = reverseList(visited); 
                if(strcmp(((getAt(reversed, 1))->loc_name), 
                    ((getAt(visited, 1))->loc_name))  < 0)
                    copy(minpath, reversed);
                else copy(minpath, visited);
                destroy(reversed);
                
            } 

            else 
            if(curr_len == *min_dist) {
                if(strcmp(((getAt(visited, 1))->loc_name), 
                    ((getAt(minpath, 1))->loc_name))  < 0) {
                    reset(minpath);

                    LocList* reversed = reverseList(visited); 
                    if(strcmp(((getAt(reversed, 1))->loc_name), 
                        ((getAt(visited, 1))->loc_name))  < 0)
                        copy(minpath, reversed);
                    else copy(minpath, visited);
                    destroy(reversed);
                    
                    //copy(minpath, visited);

                }
               
            }
            //else {
            //    printf("didn't find a smaller path\n");
                
            //}

            popfront(visited);
            popback(visited);

        } 

        else {

            pathShuffler(min_dist, rem_dest - 1, minpath, visited, unvisited, start_station);

        }

        pushback(unvisited, curr_loc);
        popback(visited);

    }
   
}


location* initLoc(char* loc_name, uint x, uint y) {
    /*
    *   Location constructor
    */
    location* loc = (location*)malloc(sizeof(location));
    strcpy(loc->loc_name, loc_name);
    loc->loc_X = x;
    loc->loc_Y = y;
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
    location* loc = initLoc(
        _getAt(cmd,0),
        atoi(_getAt(cmd,1)), 
        atoi(_getAt(cmd,2))
        );
    free(cmd);
    return loc;
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

double path_length(LocList* path, bool to_print) {
    /*
        computes a path length
    */

    if(path->size == 0) return 0.0; //return zero if the patn doesn't contain any destinations

    double total_len = 0;
    
    if(to_print) {
        printf("%s %d %d %.2lf\n", 
        path->head->data->loc_name, 
        path->head->data->loc_X, 
        path->head->data->loc_Y, 0.00);
    } 
    for(uint i = 0, j = 1; j < path->size; ++i, ++j) {
        double dist = distance(getAt(path, i), getAt(path, j));
        if(to_print) {
            location* current = getAt(path, j);
            printf("%s %d %d %.2lf\n", 
            current->loc_name, current->loc_X, current->loc_Y, dist);
        }
        total_len += dist;
    }
    return total_len;
}

#endif //ROBOT_UTILS