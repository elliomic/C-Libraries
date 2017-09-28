#ifndef ITERATORUTILITY_H
#define ITERATORUTILITY_H

#include "Iterator.h"


#define copyIter(T) copyIter##T
#define copyIterDefinition(T) \
Iterator(T) *copyIter(T)(Iterator(T) *iter) \
{ \
	Iterator(T) *newIter = newIterator(T)(iter->current, iter->gen); \
	newIter->trans = copyList(trans_fun_type##T)(iter->trans); \
	return newIter; \
}


#define applyIter(T) applyIter##T
#define applyIterDefinition(T) \
Iterator(T) *applyIter(T)(Iterator(T) *iter, trans_fun_type(T) f) \
{ \
	Iterator(T) *newIter = copyIter(T)(iter); \
	addLast(trans_fun_type##T)(newIter->trans, f); \
	return newIter; \
}


#define headIter(T) headIter##T
#define headIterDefinition(T) \
T headIter(T)(Iterator(T) *iter) \
{ \
	return currentIter(T)(iter); \
}


#define tailIter(T) tailIter##T
#define tailIterDefinition(T) \
Iterator(T) *tailIter(T)(Iterator(T) *iter) \
{ \
	Iterator(T) *newIter = copyIter(T)(iter); \
	nextIter(T)(newIter); \
	return newIter; \
}


#define takeIter(T) takeIter##T
#define takeIterDefinition(T) \
List(T) *takeIter(T)(Iterator(T) *iter, int n) \
{ \
	List(T) *list = newList(T)(); \
	T element = restartIter(T)(iter); \
	while (listSize(T)(list) < n) { \
		addLast(T)(list, element); /* addLast is too slow in this loop */ \
		element = nextIter(T)(iter); \
	} \
	return list; \
}


#define freeIter(T) freeIter##T
#define freeIterDefinition(T) \
void freeIter(T)(Iterator(T) *iter) \
{ \
	freeList(trans_fun_type##T)(iter->trans); \
	free(iter); \
}


#define IteratorUtilityLib(T) \
copyIterDefinition(T) \
\
applyIterDefinition(T) \
\
headIterDefinition(T) \
\
tailIterDefinition(T) \
\
takeIterDefinition(T) \
\
freeIterDefinition(T) \


#endif
