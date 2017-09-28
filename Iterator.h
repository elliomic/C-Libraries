#ifndef ITERATOR_H
#define ITERATOR_H

#include "LinkedList.h"
#include "ListUtility.h"


int inc(int x)
{
	return x + 1;
}

int dec(int x)
{
	return x - 1;
}


#define trans_fun_type(T) trans_fun_type##T
#define trans_fun_typedef(T) typedef T (*trans_fun_type(T))(T);


#define Iterator(T) Iterator##T
#define IteratorDefinition(T) \
typedef struct Iterator(T) { \
	T start; \
	T current; \
	T (*gen)(T); \
	List(trans_fun_type##T) *trans; \
} Iterator(T);


#define newIterator(T) newIterator##T
#define newIteratorDefinition(T) \
Iterator(T) *newIterator(T)(T start, T(*gen)(T)) \
{ \
	Iterator(T) *iter = malloc(sizeof(Iterator(T))); \
	iter->start = iter->current = start; \
	iter->gen = gen; \
	iter->trans = newList(trans_fun_type##T)(); \
	return iter; \
}

#define listTransform(T) listTransform##T
#define listTransformDefinition(T) \
T listTransform(T)(List(trans_fun_type##T) *trans, T e) \
{ \
	if (listSize(trans_fun_type##T)(trans) == 0) { \
		return e; \
	} \
\
	List(trans_fun_type##T) *tail = tailList(trans_fun_type##T)(trans); \
	T ret = listTransform(T)(tail, \
	                         headList(trans_fun_type##T)(trans)(e)); \
	free(tail); \
	return ret; \
}

#define currentIter(T) currentIter##T
#define currentIterDefinition(T) \
T currentIter(T)(Iterator(T) *iter) \
{ \
	return listTransform(T)(iter->trans, iter->current); \
}

#define nextIter(T) nextIter##T
#define nextIterDefinition(T) \
T nextIter(T)(Iterator(T) *iter) \
{ \
	iter->current = iter->gen(iter->current); \
	return listTransform(T)(iter->trans, iter->current); \
}

#define restartIter(T) restartIter##T
#define restartIterDefinition(T) \
T restartIter(T)(Iterator(T) *iter) \
{ \
	iter->current = iter->start; \
	return listTransform(T)(iter->trans, iter->current); \
}


#define IteratorLib(T) \
trans_fun_typedef(T) \
\
LinkedListLib(trans_fun_type(T)) \
\
ListUtilityLib(trans_fun_type(T)) \
\
IteratorDefinition(T) \
\
newIteratorDefinition(T) \
\
listTransformDefinition(T) \
\
currentIterDefinition(T) \
\
nextIterDefinition(T) \
\
restartIterDefinition(T) \


#endif
