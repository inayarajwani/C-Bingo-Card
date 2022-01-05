/* source: list.c */
/* purpose: implementation of list ADT */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void init(struct List *listAddress, int size) {
/* Purpose: Initializes List struct with inputted size
   Expects: Address of List struct and maximum size; i.e. init(&myList, 77);
*/

    listAddress->listptr=(int *) calloc (size, sizeof(int));
    listAddress->maxSize=size;
    listAddress->currentSize=0;
}

int add(struct List *listAddress, int element) {
/* Purpose: Adds element to the specified list. Returns 0 if list is full, 1 otherwise.
   Expects: address of List struct and number to add to List; i.e. add(&myList, 77);
*/

    if (listAddress->currentSize >= listAddress->maxSize) { return 0; } // don't add if full
    else {
        *(listAddress->listptr)=element;
        listAddress->listptr++;
        listAddress->currentSize++;
    return 1;
    }
}

int check(struct List *listAddress, int element) {
/* Checks if element exists in list. Returns 0 if false, 1 otherwise.
   Expects: address of List struct and element; i.e. check(&myList, 77);
*/

    int *first = listAddress->listptr - listAddress->currentSize; // pointer to first address of list

    for(int i=0; i < listAddress->currentSize; i++) {
        if (element==*first) { return 1; }
        first++;
    }
    return 0;
}

char getCallLet(int callInt) {
/* Purpose: assigns letter to valid call number.
   Expects: call number in range [1-75]; i.e. getCallLet(66);
*/

    callInt=(callInt-1)/15; //sorts call number into ranges based on multiples of 15
    char callLet;

    switch(callInt) { //then assigns call number to a letter based on its range
        case 0 : callLet='L';
        break;
        case 1 : callLet='I';
        break;
        case 2 : callLet='N';
        break;
        case 3 : callLet='U';
        break;
        case 4 : callLet='X';
        break;
    }
//      printf("**** callInt=%d, callLet=%c ", callInt, callLet); //diagnostic
    return callLet;
}

void print(struct List *listAddress) {
/* Purpose: Prints all the elements in list.
   Expects: address of a List struct; i.e. print(&myList);
*/

    int *ptr=listAddress->listptr;
    int *first = ptr - (listAddress->currentSize); // pointer to first address of list

    printf("Call List: ");

    for(int i=0; i < listAddress->currentSize; i++) {
        char callLet=getCallLet(*first);
        printf("%c%02d ", callLet, *first);
        first++;
    }

    printf("\n");
}

//helper function for debugging
void lastValue(struct List *list) {
    int *ptr=list->listptr;
    ptr--;
    printf("last value=%d\n\n",*ptr);

}
