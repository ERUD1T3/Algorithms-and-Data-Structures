#ifndef QUERYING_H 
#define QUERYING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TTree.h"


/**************************************
 * QUERY METHODS PROTOTYPES 
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
void processQuery(TTree* taxonomy, TNList* query_list);


/**************************************
 * QUERY METHODS
 *************************************/ 


void directSuperCategory(TTree* taxonomy, char* category) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    printf("%s", target->parent->data);
}

void directSubCategories(TTree* taxonomy, char* category) {
    /*
    *return the data in the children list
    */
    TNode* target = searchNode(taxonomy, category);
    printlist(target->children);
}

void allSuperCategories(TTree* taxonomy, char* category) {
    /*
    *return data in all ancestors
    */
    TNode* target = searchNode(taxonomy, category);
    TNode* ancestor = target->parent;
    while(ancestor != NULL) {
        printf("%s ", ancestor->data);
        ancestor = ancestor->parent;
    }
}

void allSubCategories(TTree* taxonomy, char* category) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    preOrder(target, NULL);
}

//UNDER CONSTRUCTION
void numberOfAllSuperCategories(TTree* taxonomy, char* category) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    TNode* ancestor = target->parent;
    uint counter = 0;
    while(ancestor != NULL) {
        //printf("%s", ancestor->data);
        ++counter;
        ancestor = ancestor->parent;
    }
    printf("%d", counter);

}

//UNDER CONSTRUCTION
void numberOfAllSubCategories(TTree* taxonomy, char* category) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    uint counter = 0;
    preOrder(target, &counter);
    printf("%d", counter - 1); //removing the root of the subtree
}

void isSuperCategory(TTree* taxonomy, char* category, char* supercategory) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    if(!strcmp(target->parent->data, supercategory)) printf("yes");
    else printf("no");
}

void isSubCategory(TTree* taxonomy, char* category, char* subcategory) {
    /*
    *return the data in the parent of the category
    */
    TNode* target = searchNode(taxonomy, category);
    if(preOrderSearch(target, subcategory) != NULL) printf("yes");
    else printf("no");
}

//UNDER CONSTRUCTION
void closestCommonSupercategory(TTree* taxonomy, char* category1, char* category2) {
    /*
    *return the data in the parent of the category
    */
    TNode* target1 = searchNode(taxonomy, category1);
    TNode* target2 = searchNode(taxonomy, category2);

    TNList* ancestors = initTNList();
    TNode* ancestor = target1->parent;

    while(ancestor != NULL) {
        pushback(ancestors, ancestor->data);
        ancestor = ancestor->parent;
    }

    ancestor = target2->parent;
    while(ancestor != NULL) {
        for(uint i = 0; i < ancestors->size; ++i) {
            if(!strcmp(ancestor->data, getAt(ancestors, i))) {
                printf("%s", ancestor->data);
                return;
            }
        }
        ancestor = ancestor->parent;
    }
}


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





#endif //QUERYING_H 