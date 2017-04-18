#ifndef LISTUTILITY_H
#define LISTUTILITY_H

#include "LinkedList.c"


#define deepCopyList(T) deepCopyList##T
#define deepCopyListDefinition(T) \
List(T) * deepCopyList(T)(List(T) * list) { \
	List(T) * newList = constructList(T)(); \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		addLast(T)(newList, n->element); \
		n = n->next; \
	} \
	return newList; \
}


#define headList(T) headList##T
#define headListDefinition(T) \
T headList(T)(List(T) * list) { \
	return list->head->element; \
}


#define tailList(T) tailList##T
#define tailListDefinition(T) \
List(T) * tailList(T)(List(T) * list) { \
	List(T) * newList = deepCopyList(T)(list); \
	Node(T) * h = newList->head; \
\
	if (h != NULL) { \
		newList->head = newList->head->next; \
		free(h); \
	} \
\
	return newList; \
}


#define concatList(T) concatList##T
#define concatListDefinition(T) \
List(T) * concatList(T)(List(T) * list1, List(T) * list2) { \
	List(T) * newList = deepCopyList(T)(list1); \
	List(T) * newList2 = deepCopyList(T)(list2); \
	getNode(T)(newList, getSize(T)(newList) - 1)->next = newList2->head; \
	free(newList2); \
	return newList; \
}


#define mapList(T) mapList##T
#define mapListDefinition(T) \
void mapList(T)(List(T) * list, void (f)(T)) { \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		f(n->element); \
		n = n->next; \
	} \
}


#define projectList(T,U) projectList##T##U
#define projectListDefinition(T,U) \
List(U) * projectList(T,U)(List(T) * list, U (f)(T)) { \
	List(U) * newList = constructList(U)(); \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		addLast(U)(newList, f(n->element)); \
		n = n->next; \
	} \
	return newList; \
}


#define ListUtilityLib(T) \
deepCopyListDefinition(T) \
\
headListDefinition(T) \
\
tailListDefinition(T) \
\
concatListDefinition(T) \
\
mapListDefinition(T) \


#endif
