#ifndef ITERATORUTILITY_H
#define ITERATORUTILITY_H

#include "Iterator.c"
#include "LinkedList.c"


#define deepCopyIter(T) deepCopyIter##T
#define deepCopyIterDefinition(T) \
Iterator(T) * deepCopyIter(T)(Iterator(T) * iter) \
{ \
	Iterator(T) * newIterator = constructIterator(T)(iter->current, iter->gen); \
	newIterator->trans = iter->trans; \
	return newIterator; \
}


#define headIter(T) headIter##T
#define headIterDefinition(T) \
T headIter(T)(Iterator(T) * iter) \
{ \
	return currentIter(T)(iter); \
}


#define tailIter(T) tailIter##T
#define tailIterDefinition(T) \
Iterator(T) * tailIter(T)(Iterator(T) * iter) \
{ \
	return constructIterator(T)(nextIter(T)(iter), iter->gen); \
}


#define take(T) take##T
#define takeDefinition(T) \
List(T) * take(T)(Iterator(T) * iter, int n) \
{ \
	List(T) * list = constructList(T)(); \
	Node(T) * cur = list->head = constructNode(T)(currentIter(T)(iter), NULL); \
\
	while (list->size < n) { \
		cur->next = constructNode(int)(nextIter(T)(iter), NULL); \
		cur = cur->next; \
		list->size++; \
	} \
\
	return list; \
}


#define IteratorUtilityLib(T) \
deepCopyIterDefinition(T) \
\
headIterDefinition(T) \
\
tailIterDefinition(T) \
\
takeDefinition(T) \


#endif
