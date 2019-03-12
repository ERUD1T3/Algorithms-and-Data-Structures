#ifndef QUERIES_H
#define QUERIES_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Heap.h"

EnterBid time name price quantity
UpdateMinimumAcceptablePrice time price
SellOneItem time
DisplayHighestBid time

void processQuery(TTree* taxonomy, TNList* query_list) {
    /*
    *   Executes the right query on the Taxonomy tree
    */ 

    if(!strcmp(getAt(query_list, 0), "DirectSupercategory")) {
        directSuperCategory(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "DirectSubcategories")) {
        directSubCategories(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "AllSupercategories")) {
        allSuperCategories(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "AllSubcategories")) {
        allSubCategories(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "NumberOfAllSupercategories")) {
        numberOfAllSuperCategories(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "NumberOfAllSubcategories")) {
        numberOfAllSubCategories(taxonomy, getAt(query_list, 1));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "IsSupercategory")) {
        isSuperCategory(taxonomy, getAt(query_list, 1), getAt(query_list, 2));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "IsSubcategory")) {
        isSubCategory(taxonomy, getAt(query_list, 1), getAt(query_list, 2));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "ClosestCommonSupercategory")) {
        closestCommonSupercategory(taxonomy, getAt(query_list, 1), getAt(query_list, 2));
    }
    else printf("Invalid command!\n");
}

#endif // QUERIES_H