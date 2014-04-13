#include "list.h"
#include <stdlib.h> 

static LIST* insert(int i, int j, int n);

static LIST* insert(int i, int j, int n) {
	LIST* ret = (LIST*) malloc(sizeof* ret);
	
	if (ret != NULL)
		ret->i = i, ret->j = j, ret->nbPossibleValues = n, ret->next = NULL;
		
	return ret;
}

void deleteList(LIST** list) {
	LIST* tmp;
	
	while ((tmp = *list) != NULL)
		*list = (*list)->next, free(tmp);
}

void pushFront(LIST** list, int i, int j, int n) {
	LIST* first = insert(i, j, n);
	
	if (first != NULL)
		first->next = *list, *list = first;
}

/* /!\ The list must be sorted */
void insertSorted(LIST** list, LIST* elem) {
	if (*list == NULL)
		*list = elem, elem->next = NULL;
	else if ((*list)->nbPossibleValues < elem->nbPossibleValues)
		insertSorted(&(*list)->next, elem);
	else
		elem->next = *list, *list = elem;
}

LIST* insertionSort(LIST* list) {
	LIST *curr, *list2 = NULL, *tmp;
	
	for (curr = list; curr != NULL; curr = tmp) {
		tmp = curr->next;
		insertSorted(&list2, curr);
	}
	
	return list2;
}
