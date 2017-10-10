#ifndef STRING_H
#define STRING_H

#include <math.h>
#include "typedefs.h"
#include "LinkedList.h"
#include "ListUtility.h"

LinkedListLib(char)
ListUtilityLib(char)
LinkedListLib(char_p)
arrayToListDefinition(char_p)

typedef List(char) * String;

LinkedListLib(String)
projectListDefinition(char_p, String)

String newString(const char_p literal)
{
	if (literal[0] == '\0') return newList(char)();
	else return
		     addFirst(char)(
			     newString(literal + 1),
			     literal[0]);
}

int slength(String string)
{
	return listSize(char)(string);
}

void printc(char c)
{
	putchar(c);
}

void prints(String string)
{
	applyList(char)(string, printc);
}

String sreverse(String string)
{
	if (emptyList(char)(string)) return newList(char)();
	else return
		     addLast(char)(
			     sreverse(
				     tailList(char)(string)),
			     headList(char)(string));
}

#define toUInt(T) toUInt##T
unsigned int toUInt(String)(String string)
{
	char h = headList(char)(string);

	if (h >= '0' && h <= '9') {
		if (listSize(char)(string) == 1) return h - '0';
		else return (h - '0') * pow(10, listSize(char)(string) - 1) + toUInt(String)(tailList(char)(string));
	}

	die("error: conversion from string to unsigned int failed");
}

#define toInt(T) toInt##T
int toInt(String)(String string)
{
	char h = headList(char)(string);

	if (h == '-') return -1 * toUInt(String)(tailList(char)(string));
	if (h == '+') return toUInt(String)(tailList(char)(string));
	if (h >= '0' && h <= '9') return toUInt(String)(string);

	die("error: conversion from string to int failed");
}

List(String) *convertArgs(int argc, char_p *argv)
{
	return projectList(char_p, String)(arrayToList(char_p)(argv, argc), newString);
}

#endif
