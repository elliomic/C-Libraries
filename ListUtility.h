#ifndef LISTUTILITY_H
#define LISTUTILITY_H

#include "LinkedList.h"


#define copyList(T) copyList##T
#define copyListDefinition(T) \
List(T) *copyList(T)(List(T) *list) \
{ \
	List(T) *listCopy = newList(T)(); \
	Node(T) *n = list->head; \
\
	while (n != NULL) { \
		addLast(T)(listCopy, n->element); \
		n = nextNode(T)(n); \
	} \
	return listCopy; \
}


#define headList(T) headList##T
#define headListDefinition(T) \
T headList(T)(List(T) *list) \
{ \
	if (list->head != NULL) return nodeElement(T)(list->head); \
	die("error: head of empty list"); \
}


#define tailList(T) tailList##T
#define tailListDefinition(T) \
List(T) *tailList(T)(List(T) *list) \
{ \
	if (emptyList(T)(list)) die("error: tail of empty list") ; \
\
	List(T) *tail = newList(T)(); \
	Node(T) *h = list->head; \
\
	if (h != NULL) { \
		tail->head = nextNode(T)(list->head); \
		tail->size = listSize(T)(list) - 1; \
	} \
\
	return tail; \
}


#define concatList(T) concatList##T
#define concatListDefinition(T) \
List(T) *concatList(T)(List(T) *list1, List(T) *list2) \
{ \
	List(T) *listCopy = copyList(T)(list1); \
	List(T) *listCopy2 = copyList(T)(list2); \
	getNode(T)(listCopy, listSize(T)(listCopy) - 1)->next = listCopy2->head; \
	listCopy->size = listSize(T)(list1) + listSize(T)(list2); \
	free(listCopy2); \
	return listCopy; \
}


#define applyList(T) applyList##T
#define applyListDefinition(T) \
void applyList(T)(List(T) *list, void (f)(T)) \
{ \
	Node(T) *n = list->head; \
\
	while (n != NULL) { \
		f(n->element); \
		n = nextNode(T)(n); \
	} \
}


#define projectList(T,U) projectList##T##U
#define projectListDefinition(T,U) \
List(U) *projectList(T,U)(List(T) *list, U (f)(T)) \
{ \
	List(U) *listCopy = newList(U)(); \
	Node(T) *n = list->head; \
\
	while (n != NULL) { \
		addLast(U)(listCopy, f(n->element)); \
		n = nextNode(T)(n); \
	} \
	return listCopy; \
}


#define arrayToList(T) arrayToList##T
#define arrayToListDefinition(T) \
List(T) *arrayToList(T)(T *array, int size) \
{ \
	List(T) *list = newList(T)(); \
	{ \
		int i; \
		for (i = 0; i < size; i++) { \
			addLast(T)(list, array[i]); \
		} \
	} \
	return list; \
}


#define freeList(T) freeList##T
#define freeListDefinition(T) \
void freeList(T)(List(T) *list) \
{ \
	Node(T) *current; \
	Node(T) *next; \
	current = list->head; \
\
	while (current != NULL) { \
		next = nextNode(T)(current); \
		free(current); \
		current = next; \
	} \
\
	free(list); \
}


#define ListUtilityLib(T) \
copyListDefinition(T) \
\
headListDefinition(T) \
\
tailListDefinition(T) \
\
concatListDefinition(T) \
\
applyListDefinition(T) \
\
arrayToListDefinition(T) \
\
freeListDefinition(T) \


#endif
