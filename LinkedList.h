#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdbool.h>
#include "gc.h"
#include "debug.h"

/*
  Node struct for use in Linked Lists. Contains an element of type T and a
  pointer to the next node.
 */
#define Node(T) Node##T
#define NodeDefinition(T) \
typedef struct Node(T) { \
	T element; \
	struct Node(T) *next; \
} Node(T);


/*
  List struct used as the main building block for this library. Contains a head
  pointer to the first element of the list as well as a foot pointer to the last
  element of the list. Also has the size of the list.
 */
#define List(T) List##T
#define ListDefinition(T) \
typedef struct List(T) { \
	Node(T) *head; \
	Node(T) *foot; \
	int size; \
} List(T);


/*
  Links two nodes together. Sets the next property of the first node to point to
  the second.
 */
#define linkNodes(T) linkNodes##T
#define linkNodesDefinition(T) \
Node(T) *linkNodes(T)(Node(T) *first, Node(T) *second) \
{ \
	first->next = second; \
	return first; \
}


/*
  Sets the element of a node to the given value.
 */
#define setNodeElement(T) setNodeElement##T
#define setNodeElementDefinition(T) \
Node(T) *setNodeElement(T)(Node(T) *node, T element) \
{ \
	node->element = element; \
	return node; \
}


/*
  Creates a new node containing the specified element with the next property
  pointing to the specified node.
 */
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


/*
  Sets the head property of a list to point to the specified node.
 */
#define setListHead(T) setListHead##T
#define setListHeadDefinition(T) \
List(T) *setListHead(T)(List(T) *list, Node(T) *node) \
{ \
	list->head = node; \
	return list; \
}


/*
  Sets the foot property of a list to point to the specified node.
 */
#define setListFoot(T) setListFoot##T
#define setListFootDefinition(T) \
List(T) *setListFoot(T)(List(T) *list, Node(T) *node) \
{ \
	list->foot = node; \
	return list; \
}


/*
  Sets the size property of a list to point to the specified size.
 */
#define setListSize(T) setListSize##T
#define setListSizeDefinition(T) \
List(T) *setListSize(T)(List(T) *list, int size)	\
{ \
	list->size = size; \
	return list; \
}


/*
  Creates a new empty list with no head or foot and size 0.
 */
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


/*
  Returns the element stored in the given node.
 */
#define nodeElement(T) nodeElement##T
#define nodeElementDefinition(T) \
T nodeElement(T)(Node(T) *node) \
{ \
	return node->element; \
}


/*
  Returns the node after the given one.
 */
#define nextNode(T) nextNode##T
#define nextNodeDefinition(T) \
Node(T) *nextNode(T)(Node(T) *node) \
{ \
	return node->next; \
}


/*
  Returns the size of the given list.
 */
#define listSize(T) listSize##T
#define listSizeDefinition(T) \
int listSize(T)(List(T) *list) \
{ \
	return list->size; \
}


/*
  Returns TRUE if the list is empty, FALSE otherwise.
 */
#define emptyList(T) emptyList##T
#define emptyListDefinition(T) \
bool emptyList(T)(List(T) *list) \
{ \
	return listSize(T)(list) == 0; \
}


/*
  Increments the size of the list by 1.
 */
#define incListSize(T) incListSize##T
#define incListSizeDefinition(T) \
List(T) *incListSize(T)(List(T) *list)	\
{ \
	list->size++; \
	return list; \
}


/*
  Returns TRUE if the index is within the bounds of the list, dies otherwise.
 */
#define checkIndexBounds(T) checkIndexBounds##T
#define checkIndexBoundsDefinition(T) \
bool checkIndexBounds(T)(List(T) *list, int index) \
{ \
	if (index >= listSize(T)(list) || index < 0) die("error: index out of bounds"); \
	else return true; \
}


/*
  Returns the node at the specified index.
 */
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


/*
  Returns the first element of the list, dies if empty.
 */
#define headList(T) headList##T
#define headListDefinition(T) \
T headList(T)(List(T) *list) \
{ \
	if (list->head != NULL) return nodeElement(T)(list->head); \
	die("error: head of empty list"); \
}


/*
  Returns the list of all elements of a list but the first one.
 */
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


/*
  Checks if the list is empty and sets the foot equal to the head if it is.
  Called during the mutable version of the addFirst function.
 */
#define addFirstMutableEmpty(T) addFirstMutableEmpty##T
#define addFirstMutableEmptyDefinition(T) \
List(T) *addFirstMutableEmpty(T)(List(T) *list) \
{ \
	if (emptyList(T)(list)) return setListFoot(T)(list, list->head); \
}


/*
  Adds the given object in front of the given list. Modifies the original list.
  You should usually use normal addFirst instead.
 */
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


/*
  Checks if the original list is empty and sets the foot equal to the head if it
  is. Called during the addFirst function.
 */
#define addFirstEmpty(T) addFirstEmpty##T
#define addFirstEmptyDefinition(T) \
List(T) *addFirstEmpty(T)(List(T) *orig, List(T) *list) \
{ \
	if (emptyList(T)(orig)) return setListFoot(T)(list, list->head); \
	else return setListFoot(T)(list, orig->foot); \
}


/*
  Adds the given object in front of a copy of the given list and returns the
  result. This is the preferred method of adding an item to a list.
 */
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


/*
  Creates a deep copy of the specified list.
 */
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


/*
  Checks if the specified node is the foot of the given list. If it is, sets the
  foot of the list to the node that comes after the given one.
 */
#define addAfterFoot(T) addAfterFoot##T
#define addAfterFootDefinition(T) \
List(T) *addAfterFoot(T)(List(T) *list, Node(T) *node) \
{ \
	if (node == list->foot) return setListFoot(T)(list, nextNode(T)(node)); \
}


/*
  Adds the given object after the specified node in the given list. Modifies the
  original list.
 */
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


/*
  Adds the given object at the end of the given list. Modifies the original list.
  You should usually use normal addLast instead.
 */
#define addLastMutable(T) addLastMutable##T
#define addLastMutableDefinition(T) \
List(T) *addLastMutable(T)(List(T) *list, T thing) \
{ \
	if (emptyList(T)(list)) return addFirstMutable(T)(list, thing); \
	else return addAfter(T)(list, list->foot, thing); \
}


/*
  Adds the given object at the end of a copy of the given list and returns the
  result. This is the preferred method of adding an item to the end of a list.
 */
#define addLast(T) addLast##T
#define addLastDefinition(T) \
List(T) *addLast(T)(List(T) *list, T thing) \
{ \
	return addLastMutable(T)(copyList(T)(list), thing); \
}


/*
  Adds the given object at the index specified of a copy of the given list
  between the node and the index before and the node that used to be at that
  index.
 */
#define addIndex(T) addIndex##T
#define addIndexDefinition(T) \
List(T) *addIndex(T)(List(T) *list, int index, T thing) \
{ \
	if (index == 0) return addFirst(T)(list, thing); \
	else if (index == listSize(T)(list)) return addLast(T)(list, thing); \
	else return addAfter(T)(copyList(T)(list), getNode(T)(list, index - 1), thing); \
}


/*
  Returns the element stored at the given index.
 */
#define getElement(T) getElement##T
#define getElementDefinition(T) \
T getElement(T)(List(T) *list, int index) \
{ \
	return nodeElement(T)(getNode(T)(list, index)); \
}


/*
  Stores the given  element at the given index.
 */
#define setElement(T) setElement##T
#define setElementDefinition(T) \
T setElement(T)(List(T) *list, int index, T thing) \
{ \
	Node(T) *e = getNode(T)(list, index); \
	T oldElement = nodeElement(T)(e); \
	e->element = thing; \
	return oldElement; \
}


/*
  Removes the node at the specified index. The node after the removed node will
  now be at the specified index.
 */
#define removeIndex(T) removeIndex##T
#define removeIndexDefinition(T) \
T removeIndex(T)(List(T) *list, int index) \
{ \
	Node(T) *previous = getNode(T)(list, index - 1); \
	Node(T) *thing = nextNode(T)(previous); \
\
	linkNodes(T)(previous, nextNode(T)(thing)); \
	list->size--; \
\
	return nodeElement(T)(thing); \
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


/*
  Returns the index of the first occurance of the given object in the specified
  list after the given index.
 */
#define indexOfAfter(T) indexOfAfter##T
#define indexOfAfterDefinition(T) \
int indexOfAfter(T)(List(T) *list, T thing, int index) \
{ \
	if (headList(T)(list) == thing) return index; \
	else if (listSize(T)(list) == 1) return -1; \
	else return indexOfAfter(T)(list, thing, index + 1); \
}


/*
  Returns the index of the first occurance of the given object in the specified
  list.
 */
#define indexOf(T) indexOf##T
#define indexOfDefinition(T) \
int indexOf(T)(List(T) *list, T thing) \
{ \
	return indexOfAfter(T)(list, thing, 0); \
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
indexOfAfterDefinition(T) \
\
indexOfDefinition(T) \
\

#endif
