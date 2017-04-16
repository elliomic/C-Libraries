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
	T (*trans)(T); \
} Iterator(T);


#define identity(T) identity##T
#define identityDefinition(T) \
T identity(T)(T e) { \
	return e; \
}


#define constructIterator(T) constructIterator##T
#define constructIteratorDefinition(T) \
Iterator(T) * constructIterator(T)(T start, T(*gen)(T) ) { \
	Iterator(T) * iter = malloc(sizeof(Iterator(T))); \
	iter->current = start; \
	iter->gen = gen; \
	iter->trans = *identity(T); \
	return iter; \
}


#define currentIter(T) currentIter##T
#define currentIterDefinition(T) \
T currentIter(T)(Iterator(T) * iter) { \
	return iter->trans(iter->current); \
}


#define nextIter(T) nextIter##T
#define nextIterDefinition(T) \
T nextIter(T)(Iterator(T) * iter) { \
	iter->current = iter->gen(iter->current); \
	return iter->trans(iter->current); \
}


#define IteratorLib(T) \
LinkedListLib(T) \
\
IteratorDefinition(T) \
\
identityDefinition(T) \
\
constructIteratorDefinition(T)	\
\
currentIterDefinition(T) \
\
nextIterDefinition(T) \
\
takeDefinition(T) \


#endif
