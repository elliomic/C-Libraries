#ifndef FUNCLIB_H
#define FUNCLIB_H

#include "LinkedList.h"


#define deepCopy(T) deepCopy##T
#define deepCopyDefinition(T) \
List(T) * deepCopy(T)(List(T) * list) { \
	List(T) * newList = constructList(T)(); \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		addLast(T)(newList, n->element); \
		n = n->next; \
	} \
	return newList; \
}


#define head(T) head##T
#define headDefinition(T) \
T head(T)(List(T) * list) { \
	return list->head->element; \
}


#define tail(T) tail##T
#define tailDefinition(T) \
List(T) * tail(T)(List(T) * list) { \
	List(T) * newList = deepCopy(T)(list); \
	Node(T) * h = newList->head; \
\
	if (h != NULL) { \
		newList->head = newList->head->next; \
		free(h); \
	} \
\
	return newList; \
}


#define concat(T) concat##T
#define concatDefinition(T) \
List(T) * concat(T)(List(T) * list1, List(T) * list2) { \
	List(T) * newList = deepCopy(T)(list1); \
	List(T) * newList2 = deepCopy(T)(list2); \
	getNode(T)(newList, getSize(T)(newList) - 1)->next = newList2->head; \
	free(newList2); \
	return newList; \
}


#define map(T) map##T
#define mapDefinition(T) \
void map(T)(List(T) * list, void (f)(T)) { \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		f(n->element); \
		n = n->next; \
	} \
}


#define project(T,U) project##T##U
#define projectDefinition(T,U) \
List(U) * project(T,U)(List(T) * list, U (f)(T)) { \
	List(U) * newList = constructList(U)(); \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		addLast(U)(newList, f(n->element)); \
		n = n->next; \
	} \
	return newList; \
}


#define funcLib(T) \
LinkedListLib(T) \
\
deepCopyDefinition(T) \
\
headDefinition(T) \
\
tailDefinition(T)\
\
concatDefinition(T) \
\
mapDefinition(T)\

#endif
