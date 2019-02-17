#ifndef BINSEARCH_H
#define BINSEARCH_H

int binarySearch(const int arr[], int low, int high, int target) {
    /*
    * Function iteratively find the index of an element in array 
    * and return that index
    * O(lgN)
    */

    int mid; //middle index 

    while (low <= high) {
        mid = low + ( high -  low)/2;

        if(arr[mid] ==  target) { //found target
            return mid;  //returning index of target
        }
        else if(arr[mid] <  target) { //target is on the right
            low = mid + 1; //dividing the search space
        }
        else { //target is on the left
            high = mid - 1;
        }
    }
    return -1; //target not found in array
}

#endif 
