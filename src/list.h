#ifndef LIST_H
#define LIST_H

#include <stdlib.h> 

typedef struct _LIST {
	int i, j, nbPossibleValues;
	struct _LIST *next;
} LIST;

void deleteList(LIST** list);
void pushFront(LIST** list, int i, int j, int n);
void insertSorted(LIST** list, LIST* elem);
LIST* insertionSort(LIST* list);

#endif
