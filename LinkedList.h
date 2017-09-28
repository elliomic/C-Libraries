#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <execinfo.h>


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
	int size; \
} List(T);


#define newNode(T) newNode##T
#define newNodeDefinition(T) \
Node(T) *newNode(T)(T element, Node(T) *next) \
{ \
	Node(T) *node = malloc(sizeof(Node(T))); \
	node->element = element; \
	node->next = next; \
	return node; \
}


#define newList(T) newList##T
#define newListDefinition(T) \
List(T) *newList(T)(void) \
{ \
	List(T) *list = malloc(sizeof(List(T))); \
	list->size = 0; \
	return list; \
}


#define nodeElement(t) nodeElement##t
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


void die(const char *message)
{
	int size = 10000;
	void *buffer[size];
	size = backtrace(buffer, size);
	fputs(message, stderr);
	fputc('\n', stderr);
	backtrace_symbols_fd(buffer, size, 2);
	exit(1);
}


#define checkIndexBounds(T) checkIndexBounds##T
#define checkIndexBoundsDefinition(T) \
void checkIndexBounds(T)(List(T) *list, int index) \
{ \
	if (index >= listSize(T)(list) || index < 0) die("error: index out of bounds"); \
}


#define listSize(T) listSize##T
#define listSizeDefinition(T) \
int listSize(T)(List(T) *list) \
{ \
	return list->size; \
}


#define clearList(T) clearList##T
#define clearListDefinition(T) \
void clearList(T)(List(T) *list) \
{ \
	Node(T) *e = list->head; \
\
	while (e != NULL) { \
		Node(T) *next = nextNode(T)(e); \
		free(e); \
		e = next; \
	} \
\
	list->size = 0; \
}


#define emptyList(T) emptyList##T
#define emptyListDefinition(T) \
bool emptyList(T)(List(T) *list) \
{ \
	return listSize(T)(list) == 0; \
}


#define addFirst(T) addFirst##T
#define addFirstDefinition(T) \
void addFirst(T)(List(T) *list, T thing) \
{ \
	Node(T) *newNode = newNode(T)(thing, list->head); \
	list->head = newNode; \
	list->size++; \
}


#define getNode(T) getNode##T
#define getNodeDefinition(T) \
Node(T) *getNode(T)(List(T) *list, int index) \
{ \
	Node(T) *thing; \
	checkIndexBounds(T)(list, index); \
\
	thing = list->head; \
\
	{ \
		int i = 0; \
		while (i < index) { \
			thing = nextNode(T)(thing); \
			i++; \
		} \
	} \
\
	return thing; \
}


#define addIndex(T) addIndex##T
#define addIndexDefinition(T) \
void addIndex(T)(List(T) *list, int index, T thing) \
{ \
	if (index == 0) \
	{ \
		addFirst(T)(list, thing); \
		return; \
	} \
\
	Node(T) *previous = getNode(T)(list, index - 1); \
	Node(T) *newNode = newNode(T)(thing, nextNode(T)(previous)); \
	previous->next = newNode; \
	list->size++; \
}


#define addLast(T) addLast##T
#define addLastDefinition(T) \
void addLast(T)(List(T) *list, T thing) \
{ \
	addIndex(T)(list, listSize(T)(list), thing); \
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
	previous->next = nextNode(T)(thing); \
	list->size--; \
\
	free(thing); \
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


#define printList(T) printList##T
#define printListDefinition(T,P) \
void printList(T)(List(T) *list) \
{ \
	Node(T) *current = list->head; \
	putchar('['); \
	{ \
		int i; \
		for (i = 0; i < listSize(T)(list) - 1; i++) { \
			printf(P, nodeElement(T)(current)); \
			printf(", "); \
			current = nextNode(T)(current); \
		} \
	} \
	if (current != NULL) printf(P, nodeElement(T)(current)); \
	puts("]"); \
}


#define LinkedListLib(T) \
NodeDefinition(T) \
\
ListDefinition(T) \
\
newNodeDefinition(T) \
\
newListDefinition(T) \
\
nodeElementDefinition(T) \
\
nextNodeDefinition(T) \
\
listSizeDefinition(T) \
\
checkIndexBoundsDefinition(T) \
\
clearListDefinition(T) \
\
emptyListDefinition(T) \
\
addFirstDefinition(T) \
\
getNodeDefinition(T) \
\
addIndexDefinition(T) \
\
addLastDefinition(T) \
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
