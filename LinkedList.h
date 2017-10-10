#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"
#include "gc.h"

#define Node(T) Node##T
#define NodeDefinition(T) \
typedef struct Node(T) { \
	T element; \
	struct Node(T) *next; \
} Node(T);


#define List(T) List##T
#define ListDefinition(T) \
typedef struct List(T) { \
	Node(T) *head; \
	Node(T) *foot; \
	int size; \
} List(T);


#define linkNodes(T) linkNodes##T
#define linkNodesDefinition(T) \
Node(T) *linkNodes(T)(Node(T) *first, Node(T) *second) \
{ \
	first->next = second; \
	return first; \
}


#define setNodeElement(T) setNodeElement##T
#define setNodeElementDefinition(T) \
Node(T) *setNodeElement(T)(Node(T) *node, T element) \
{ \
	node->element = element; \
	return node; \
}


#define newNode(T) newNode##T
#define newNodeDefinition(T) \
Node(T) *newNode(T)(T element, Node(T) *next) \
{ \
	return \
		linkNodes(T)( \
			setNodeElement(T)( \
				tgc_alloc(&gc, sizeof(Node(T))), \
				element), \
			next); \
}


#define setListHead(T) setListHead##T
#define setListHeadDefinition(T) \
List(T) *setListHead(T)(List(T) *list, Node(T) *node) \
{ \
	list->head = node; \
	return list; \
}


#define setListFoot(T) setListFoot##T
#define setListFootDefinition(T) \
List(T) *setListFoot(T)(List(T) *list, Node(T) *node) \
{ \
	list->foot = node; \
	return list; \
}


#define setListSize(T) setListSize##T
#define setListSizeDefinition(T) \
List(T) *setListSize(T)(List(T) *list, int size)	\
{ \
	list->size = size; \
	return list; \
}


#define newList(T) newList##T
#define newListDefinition(T) \
List(T) *newList(T)(void) \
{ \
	return \
		setListSize(T)( \
			setListFoot(T)( \
				setListHead(T)( \
					tgc_alloc(&gc, sizeof(List(T))), \
					NULL), \
				NULL), \
			0); \
}


#define nodeElement(T) nodeElement##T
#define nodeElementDefinition(T) \
T nodeElement(T)(Node(T) *node) \
{ \
	return node->element; \
}


#define nextNode(T) nextNode##T
#define nextNodeDefinition(T) \
Node(T) *nextNode(T)(Node(T) *node) \
{ \
	return node->next; \
}


#define listSize(T) listSize##T
#define listSizeDefinition(T) \
int listSize(T)(List(T) *list) \
{ \
	return list->size; \
}


#define emptyList(T) emptyList##T
#define emptyListDefinition(T) \
bool emptyList(T)(List(T) *list) \
{ \
	return listSize(T)(list) == 0; \
}


#define incListSize(T) incListSize##T
#define incListSizeDefinition(T) \
List(T) *incListSize(T)(List(T) *list)	\
{ \
	list->size++; \
	return list; \
}


#define checkIndexBounds(T) checkIndexBounds##T
#define checkIndexBoundsDefinition(T) \
bool checkIndexBounds(T)(List(T) *list, int index) \
{ \
	if (index >= listSize(T)(list) || index < 0) die("error: index out of bounds"); \
	else return true; \
}


#define getNode(T) getNode##T
#define getNodeDefinition(T) \
Node(T) *getNode(T)(List(T) *list, int index) \
{ \
	Node(T) *thing; \
	int i; \
	checkIndexBounds(T)(list, index); \
\
	thing = list->head; \
\
	for (i = 0; i < index; i++) thing = nextNode(T)(thing); \
\
	return thing; \
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
	return \
		setListSize(T)( \
			setListFoot(T)( \
				setListHead(T)( \
					newList(T)(), \
					nextNode(T)(list->head)), \
				list->foot), \
			listSize(T)(list) - 1); \
}

#define addFirstMutableEmpty(T) addFirstMutableEmpty##T
#define addFirstMutableEmptyDefinition(T) \
List(T) *addFirstMutableEmpty(T)(List(T) *list) \
{ \
	if (emptyList(T)(list)) return setListFoot(T)(list, list->head); \
}


#define addFirstMutable(T) addFirstMutable##T
#define addFirstMutableDefinition(T) \
List(T) *addFirstMutable(T)(List(T) *list, T thing) \
{ \
	return \
		incListSize(T)( \
			addFirstMutableEmpty(T)( \
				setListHead(T)( \
					list, \
					newNode(T)( \
						thing, \
						list->head)))); \
}

#define addFirstEmpty(T) addFirstEmpty##T
#define addFirstEmptyDefinition(T) \
List(T) *addFirstEmpty(T)(List(T) *orig, List(T) *list) \
{ \
	if (emptyList(T)(orig)) return setListFoot(T)(list, list->head); \
	else return setListFoot(T)(list, orig->foot); \
}


#define addFirst(T) addFirst##T
#define addFirstDefinition(T) \
List(T) *addFirst(T)(List(T) *list, T thing) \
{ \
	return \
		setListSize(T)( \
			addFirstEmpty(T)( \
				list, \
				setListHead(T)( \
					newList(T)(), \
					newNode(T)(thing, list->head))), \
			listSize(T)(list) + 1); \
}


#define copyList(T) copyList##T
#define copyListDefinition(T) \
List(T) *copyList(T)(List(T) *list) \
{ \
	if (emptyList(T)(list)) return newList(T)(); \
	else return \
		     addFirst(T)( \
				     tailList(T)(list), \
			     headList(T)(list)); \
}


#define addAfterFoot(T) addAfterFoot##T
#define addAfterFootDefinition(T) \
List(T) *addAfterFoot(T)(List(T) *list, Node(T) *node) \
{ \
	if (node == list->foot) return setListFoot(T)(list, nextNode(T)(node)); \
}


#define addAfter(T) addAfter##T
#define addAfterDefinition(T) \
List(T) *addAfter(T)(List(T) *list, Node(T) *node, T thing) \
{ \
	return \
		incListSize(T)( \
			addAfterFoot(T)( \
				list, \
				linkNodes(T)( \
					node, \
					newNode(T)( \
						thing, \
						nextNode(T)(node))))); \
}


#define addLastMutable(T) addLastMutable##T
#define addLastMutableDefinition(T) \
List(T) *addLastMutable(T)(List(T) *list, T thing) \
{ \
	if (emptyList(T)(list)) return addFirstMutable(T)(list, thing); \
	else return addAfter(T)(list, list->foot, thing); \
}


#define addLast(T) addLast##T
#define addLastDefinition(T) \
List(T) *addLast(T)(List(T) *list, T thing) \
{ \
	return addLastMutable(T)(copyList(T)(list), thing); \
}


#define addIndex(T) addIndex##T
#define addIndexDefinition(T) \
List(T) *addIndex(T)(List(T) *list, int index, T thing) \
{ \
	if (index == 0) return addFirst(T)(list, thing); \
	else if (index == listSize(T)(list)) return addLast(T)(list, thing); \
	else return addAfter(T)(copyList(T)(list), getNode(T)(list, index - 1), thing); \
}


#define getElement(T) getElement##T
#define getElementDefinition(T) \
T getElement(T)(List(T) *list, int index) \
{ \
	return nodeElement(T)(getNode(T)(list, index)); \
}


#define setElement(T) setElement##T
#define setElementDefinition(T) \
T setElement(T)(List(T) *list, int index, T thing) \
{ \
	Node(T) *e = getNode(T)(list, index); \
	T oldElement = nodeElement(T)(e); \
	e->element = thing; \
	return oldElement; \
}


#define removeIndex(T) removeIndex##T
#define removeIndexDefinition(T) \
T removeIndex(T)(List(T) *list, int index) \
{ \
	Node(T) *previous = getNode(T)(list, index - 1); \
	Node(T) *thing = nextNode(T)(previous); \
\
	T element = nodeElement(T)(thing); \
	linkNodes(T)(previous, nextNode(T)(thing)); \
	list->size--; \
\
	return element; \
}


#define removeFirst(T) removeFirst##T
#define removeFirstDefinition(T) \
T removeFirst(T)(List(T) *list) \
{ \
	return removeIndex(T)(list, 0); \
}


#define removeLast(T) removeLast##T
#define removeLastDefinition(T) \
T removeLast(T)(List(T) *list) \
{ \
	return removeIndex(T)(list, listSize(T)(list)); \
}


#define indexOf(T) indexOf##T
#define indexOfDefinition(T) \
int indexOf(T)(List(T) *list, T thing) \
{ \
	int index = 0; \
	Node(T) *n = list->head; \
\
	while (n != NULL) { \
		if (nodeElement(T)(n) == thing) return index; \
		index++; \
		n = nextNode(T)(n); \
	} \
\
	return -1; \
}


#define LinkedListLib(T) \
NodeDefinition(T) \
\
ListDefinition(T) \
\
linkNodesDefinition(T) \
\
setNodeElementDefinition(T) \
\
newNodeDefinition(T)	\
\
setListHeadDefinition(T) \
\
setListFootDefinition(T) \
\
setListSizeDefinition(T) \
\
newListDefinition(T) \
\
nodeElementDefinition(T) \
\
nextNodeDefinition(T) \
\
listSizeDefinition(T) \
\
emptyListDefinition(T) \
\
incListSizeDefinition(T) \
\
checkIndexBoundsDefinition(T) \
\
addFirstMutableEmptyDefinition(T) \
\
addFirstMutableDefinition(T) \
\
addFirstEmptyDefinition(T) \
\
addFirstDefinition(T) \
\
getNodeDefinition(T) \
\
headListDefinition(T) \
\
tailListDefinition(T) \
\
copyListDefinition(T) \
\
addAfterFootDefinition(T) \
\
addAfterDefinition(T) \
\
addLastMutableDefinition(T) \
\
addLastDefinition(T) \
\
addIndexDefinition(T) \
\
getElementDefinition(T) \
\
setElementDefinition(T) \
\
removeIndexDefinition(T) \
\
removeFirstDefinition(T) \
\
removeLastDefinition(T) \
\
indexOfDefinition(T) \


#endif
