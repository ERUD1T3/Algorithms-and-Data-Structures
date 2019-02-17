/*
 * Josias Moukpe 
 * Computer Science and Engineering
 */ 

#include "HW1/SLinkedList.h"
/*
#include <stdio.h>
#include <stdlib.h>
*/
int main(void) {

    SLList* numbers = (SLList*)malloc(sizeof(SLList));

    init(numbers);

    for(unsigned int i = 0; i < 25; ++i)
        pushback(numbers, i);
    printlist(numbers);
        printf("done pushing\n");

    printf("head = %d\n", numbers->head->data);
    printf("size = %d\n", numbers->size); 
    for(unsigned int i = 0; i < 10; ++i)
        popback(numbers);
    //suppress(numbers, 2);
    printf("done poping\n");
    printlist(numbers);
    printf("size = %d\n", numbers->size);

    //printf("done printing\n");

    return 0;
}
