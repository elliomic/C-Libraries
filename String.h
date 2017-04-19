#ifndef STRING_H
#define STRING_H

#include "ListUtility.c"

printListDefinition(char, "'%c'")

#define String List(char)*

String newString(char* literal)
{
	String string = constructList(char)();
	
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
	return string->size;
}

void printc(char c)
{
	putchar(c);
}

void prints(String string)
{
	applyList(char)(string, *printc);
}


List(char) * sreverse(List(char) * string)
{
	List(char) * t = tailList(char)(string);
	if (isEmpty(char)(t)) return t;

	List(char) * rt = sreverse(t);
	addLast(char)(rt, headList(char)(string));
	free(t);
	return rt;
}

#endif
