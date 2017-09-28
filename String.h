#ifndef STRING_H
#define STRING_H

#include <math.h>
#include "typedefs.h"
#include "ListUtility.h"

LinkedListLib(char)
ListUtilityLib(char)
LinkedListLib(char_p)
ListUtilityLib(char_p)

typedef List(char) * String;

LinkedListLib(String)
projectListDefinition(char_p, String)

String newString(const char_p literal)
{
	String string = newList(char)();
	
	{
		int i = 0;
		while (literal[i] != '\0') {
			addLast(char)(string, literal[i]);
			i++;
		}
	}
	
	return string;
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
	String t = tailList(char)(string);
	if (emptyList(char)(t)) return copyList(char)(string);

	String rt = sreverse(t);
	addLast(char)(rt, headList(char)(string));
	free(t);
	return rt;
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
