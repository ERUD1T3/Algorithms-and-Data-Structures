#ifndef QUERYING_H 
#define QUERYING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TTree.h"


/**************************************
 * QUERY METHODS
 *************************************/ 

void directSuperCategory(TTree* taxonomy, char* category); //print the direct parent node
void directSubCategories(TTree* taxonomy, char* category); //prints the direct children list
void allSuperCategories(TTree* taxonomy, char* category); //prints all the ancestors
void allSubCategories(TTree* taxonomy, char* category); //prints all the descendants of node
void numberOfAllSuperCategories(TTree* taxonomy, char* category); //returns the number of all supercategories
void numberOfAllSubCategories(TTree* taxonomy, char* category); //returns the number of all subcategories
void isSuperCategory(TTree* taxonomy, char* category, char* supercategory); //true if supercategory of category
void isSubCategory(TTree* taxonomy, char* category, char* subcategory); //true if subcategory of category
void closestCommonSupercategory(TTree* taxonomy, char* category1, char* category2); //prints the closest common super category 




void directSuperCategory(TTree* taxonomy, char* category) {
    //return the data in the parent of the category

}




#endif //QUERYING_H 