#ifndef ITERATOR_H
#define ITERATOR_H

#include "LinkedList.h"


int inc(int x) { return x + 1; }
int dec(int x) { return x - 1; }


#define Iterator(T) Iterator##T
#define IteratorDefinition(T) \
typedef struct Iterator(T) { \
	T current; \
	T (*gen)(T); \
} Iterator(T);


#define constructIterator(T) constructIterator##T
#define constructIteratorDefinition(T) \
Iterator(T) * constructIterator(T)(T start, T(*gen)(T) ) { \
	Iterator(T) * iter = malloc(sizeof(Iterator(T))); \
	iter->current = start; \
	iter->gen = gen; \
	return iter; \
}


#define next(T) next##T
#define nextDefinition(T) \
T next(T)(Iterator(T) * iter) { \
	iter->current = iter->gen(iter->current); \
	return iter->current; \
}


#define take(T) take##T
#define takeDefinition(T) \
List(T) * take(T)(Iterator(T) * iter, int n) { \
	List(T) * list = constructList(T)(); \
	Node(T) * cur = list->head = constructNode(T)(iter->current, NULL); \
\
	while (list->size < n) { \
		cur->next = constructNode(int)(next(T)(iter), NULL); \
		cur = cur->next; \
		list->size++; \
	} \
\
	return list; \
}


#define IteratorLib(T) \
LinkedListLib(T) \
\
IteratorDefinition(T) \
\
constructIteratorDefinition(T)	\
\
nextDefinition(T) \
\
takeDefinition(T) \


#endif
