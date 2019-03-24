#ifndef QUERY_H
#define QUERY_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"
#include "skipList.h"


/*******************************
 * METHODS PROTOTYPES
 ******************************/

void processQuery(SList* logs, SLList* query_list);
void DisplayActivity(SList* logs,uint time);
void AddActivity(SList* logs,uint time, char* activity);
void DeleteActivity(SList* logs,uint time);
void DisplayActivitiesBetweenTimes(SList* logs,uint startTime, uint endTime);
void DisplayActivitiesFromStartTime(SList* logs,uint startTime);
void DisplayActivitiesToEndTime(SList* logs,uint endTime);
void DisplayAllActivities(SList* logs);
void PrintSkipList(SList* logs);

/************************************************
 * METHODS IMPLEMENTATION
 ***********************************************/ 

void processQuery(SList* logs, SLList* query_list) {
    /*
    *   Executes the right query on the Taxonomy tree
    */ 

    if(!strcmp(getAt(query_list, 0), "DisplayActivity")) {
        DisplayActivity(logs, atoi(getAt(query_list, 1)));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "AddActivity")) {
        AddActivity(logs, atoi(getAt(query_list, 1)), getAt(query_list, 2));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "DeleteActivity")) {
        DeleteActivity(logs, atoi(getAt(query_list, 1)));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "DisplayActivitiesBetweenTimes")) {
        DisplayActivitiesBetweenTimes(logs, atoi(getAt(query_list, 1)), atoi(getAt(query_list, 2)));
    }
    else
    if(!strcmp(getAt(query_list, 0), "DisplayActivitiesFromStartTime")) {
        DisplayActivitiesFromStartTime(logs, atoi(getAt(query_list, 1)));
    }
    else
    if(!strcmp(getAt(query_list, 0), "DisplayActivitiesToEndTime")) {
        DisplayActivitiesToEndTime(logs, atoi(getAt(query_list, 1)));
    }
    else
    if(!strcmp(getAt(query_list, 0), "DisplayAllActivities")) {
        DisplayAllActivities(logs);
    }
     else
    if(!strcmp(getAt(query_list, 0), "PrintSkipList")) {
        PrintSkipList(logs);
    }
    else printf("Invalid command!\n");
}

#endif // QUERY_H