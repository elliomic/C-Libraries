#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define Node(T) Node##T
#define NodeDefinition(T) \
typedef struct Node(T) { \
	T element; \
	struct Node(T) * next; \
} Node(T);


#define List(T) List##T
#define ListDefinition(T) \
typedef struct List(T) { \
	Node(T) * head; \
	int size; \
} List(T);


#define constructNode(T) constructNode##T
#define constructNodeDefinition(T) \
Node(T) * constructNode(T)(T element, Node(T) * next) \
{ \
	Node(T) * node = malloc(sizeof(Node(T))); \
	node->element = element; \
	node->next = next; \
	return node; \
}


#define constructList(T) constructList##T
#define constructListDefinition(T) \
List(T) * constructList(T)(void) \
{ \
	List(T) * list = malloc(sizeof(List(T))); \
	list->size = 0; \
	return list; \
}


#define getNodeElement(T) getNodeElement##T
#define getNodeElementDefinition(T) \
T getNodeElement(T)(Node(T) * node) \
{ \
	return node->element; \
}


#define getNextNode(T) getNextNode##T
#define getNextNodeDefinition(T) \
Node(T) * getNextNode(T)(Node(T) * node) \
{ \
	return node->next; \
}


#define isIndexOutOfBounds(T) isIndexOutOfBounds##T
#define isIndexOutOfBoundsDefinition(T) \
void isIndexOutOfBounds(T)(List(T) * list, int index) \
{ \
	if (index >= list->size || index < 0) { \
		fputs("error: index out of bounds\n", stderr); \
		exit(0); \
	} \
}


#define getSize(T) getSize##T
#define getSizeDefinition(T) \
int getSize(T)(List(T) * list) \
{ \
	return list->size; \
}


#define clearList(T) clearList##T
#define clearListDefinition(T) \
void clearList(T)(List(T) * list) \
{ \
	Node(T) * e = list->head; \
\
	while (e != NULL) { \
		Node(T) * next = e->next; \
		free(e); \
		e = next; \
	} \
\
	list->size = 0; \
}


#define isEmpty(T) isEmpty##T
#define isEmptyDefinition(T) \
bool isEmpty(T)(List(T) * list) \
{ \
	return list->size == 0; \
}


#define addFirst(T) addFirst##T
#define addFirstDefinition(T) \
void addFirst(T)(List(T) * list, T thing) \
{ \
	Node(T) * newNode = constructNode(T)(thing, list->head); \
	list->head = newNode; \
	list->size++; \
}


#define getNode(T) getNode##T
#define getNodeDefinition(T) \
Node(T) * getNode(T)(List(T) * list, int index) \
{ \
	Node(T) * thing; \
	isIndexOutOfBounds(T)(list, index); \
\
	thing = list->head; \
\
	{ \
		int i = 0; \
		while (i < index) { \
			thing = thing->next; \
			i++; \
		} \
	} \
\
	return thing; \
}


#define addIndex(T) addIndex##T
#define addIndexDefinition(T) \
void addIndex(T)(List(T) * list, int index, T thing) \
{ \
	if (index == 0) \
	{ \
		addFirst(T)(list, thing); \
		return; \
	} \
\
	Node(T) * previous = getNode(T)(list, index - 1); \
	Node(T) * newNode = constructNode(T)(thing, previous->next); \
	previous->next = newNode; \
	list->size++; \
}


#define addLast(T) addLast##T
#define addLastDefinition(T) \
void addLast(T)(List(T) * list, T thing) \
{ \
	addIndex(T)(list, list->size, thing); \
}


#define getElementAt(T) getElementAt##T
#define getElementAtDefinition(T) \
T getElementAt(T)(List(T) * list, int index) \
{ \
	return getNodeElement(getNode(T)(list, index)); \
}


#define setElementAt(T) setElementAt##T
#define setElementAtDefinition(T) \
T setElementAt(T)(List(T) * list, int index, T thing) \
{ \
	Node(T) * e = getNode(T)(list, index); \
	T oldElement = getNodeElement(e); \
	e->element = thing; \
	return oldElement; \
}


#define removeIndex(T) removeIndex##T
#define removeIndexDefinition(T) \
T removeIndex(T)(List(T) * list, int index) \
{ \
	Node(T) * previous = getNode(T)(list, index - 1); \
	Node(T) * thing = previous->next; \
\
	T element = getNodeElement(thing); \
	previous->next = thing->next; \
	list->size--; \
\
	free(thing); \
	return element; \
}


#define removeFirst(T) removeFirst##T
#define removeFirstDefinition(T) \
T removeFirst(T)(List(T) * list) \
{ \
	return removeIndex(T)(list, 0); \
}


#define indexOf(T) indexOf##T
#define indexOfDefinition(T) \
int indexOf(T)(List(T) * list, T thing) \
{ \
	int index = 0; \
	Node(T) * n = list->head; \
\
	while (n != NULL) { \
		if (getNodeElement(n) == thing) return index; \
		index++; \
		n = n->next; \
	} \
\
	return -1; \
}


#define printList(T) printList##T
#define printListDefinition(T,P) \
void printList(T)(List(T) * list) \
{ \
	Node(T) * current = list->head; \
	if (current == NULL) puts("[]"); \
\
	{ \
		int i; \
		putchar('['); \
		for (i = 0; i < list->size - 1; i++) { \
			printf(P, getNodeElement(current)); \
			printf(", "); \
			current = current->next; \
		} \
		printf(P, getNodeElement(current)); \
		printf("]\n"); \
	} \
}


#define LinkedListLib(T) \
NodeDefinition(T) \
\
ListDefinition(T) \
\
constructNodeDefinition(T) \
\
constructListDefinition(T) \
\
getNodeElementDefinition(T) \
\
getNextNodeDefinition(T) \
\
isIndexOutOfBoundsDefinition(T) \
\
getSizeDefinition(T) \
\
clearListDefinition(T) \
\
isEmptyDefinition(T) \
\
addFirstDefinition(T) \
\
getNodeDefinition(T) \
\
addIndexDefinition(T) \
\
addLastDefinition(T) \
\
getElementAtDefinition(T) \
\
setElementAtDefinition(T) \
\
removeIndexDefinition(T) \
\
removeFirstDefinition(T) \
\
indexOfDefinition(T) \


#endif
