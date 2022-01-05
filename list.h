/* source list.h */
/* purpose: list ADT */

struct List {
    int *listptr;
    int maxSize;
    int currentSize;
};

void init(struct List *a , int b);

int add(struct List *a, int b);

int check(struct List *a, int b);

void print(struct List *a);
