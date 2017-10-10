#ifndef LISTUTILITY_H
#define LISTUTILITY_H

#include "LinkedList.h"


#define clearList(T) clearList##T
#define clearListDefinition(T)       \
List(T) *clearList(T)(List(T) *list) \
{ \
	Node(T) *e = list->head; \
	while (e != NULL) { \
		Node(T) *next = nextNode(T)(e); \
		tgc_free(&gc, e); \
		e = next; \
	} \
\
	setListSize(T)(list, 0); \
	return list; \
}


#define concatList(T) concatList##T
#define concatListDefinition(T) \
List(T) *concatList(T)(List(T) *first, List(T) *second) \
{ \
	List(T) *listCopy = copyList(T)(first); \
	List(T) *listCopy2 = copyList(T)(second); \
	linkNodes(T)(getNode(T)(listCopy, listSize(T)(listCopy) - 1), listCopy2->head); \
	setListSize(T)(listCopy, listSize(T)(first) + listSize(T)(second)); \
	return listCopy; \
}


#define applyList(T) applyList##T
#define applyListDefinition(T) \
void applyList(T)(List(T) *list, void (f)(T)) \
{ \
	Node(T) *n; \
	for (n = list->head; n != NULL; n = nextNode(T)(n)) f(n->element); \
}


#define printList(T) printList##T
#define printListDefinition(T,P) \
void printList(T)(List(T) *list) \
{ \
	Node(T) *current = list->head; \
	int i; \
	putchar('['); \
	for (i = 0; i < listSize(T)(list) - 1; i++) { \
		printf(P, nodeElement(T)(current)); \
		printf(", "); \
		current = nextNode(T)(current); \
	} \
	if (current != NULL) printf(P, nodeElement(T)(current)); \
	puts("]"); \
}


#define projectList(T,U) projectList##T##U
#define projectListDefinition(T,U) \
List(U) *projectList(T,U)(List(T) *list, U (f)(T)) \
{ \
	if (emptyList(T)(list)) return newList(U)(); \
	else return \
		     addFirst(U)( \
			     projectList(T,U)( \
				     tailList(T)(list), \
				     f), \
			     f( \
				     headList(T)(list))); \
}


#define arrayToList(T) arrayToList##T
#define arrayToListDefinition(T) \
List(T) *arrayToList(T)(T *array, int size) \
{ \
	if (size == 0) return newList(T)(); \
	else return \
		     addFirst(T)( \
			     arrayToList(T)( \
				     array + 1, \
				     size - 1), \
			     array[0]); \
}


#define foldListR(T,U) foldListR##T##U
#define foldListRDefinition(T,U) \
U foldListR(T,U)(List(T) *list, U (f)(T, T), T base) \
{ \
	if (emptyList(T)(list)) return base; \
	else return \
		     f( \
			     headList(T)(list), \
			     foldListR(T,U)( \
				     tailList(T)(list), \
				     f, \
				     base)); \
}


#define foldListL(T,U) foldListL##T##U
#define foldListLDefinition(T,U) \
U foldListL(T,U)(List(T) *list, U (f)(T, T), T base) \
{ \
	if (emptyList(T)(list)) return base; \
	else return \
		     foldListL(T,U)( \
			     tailList(T)(list), \
			     f, \
			     f(base, \
			       headList(T)(list))); \
}


#define ListUtilityLib(T) \
clearListDefinition(T) \
\
concatListDefinition(T) \
\
applyListDefinition(T) \
\
arrayToListDefinition(T) \
\


#endif
