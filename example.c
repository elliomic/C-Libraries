/*
  A simple example program that prints out the first argument it receives.
 */

#define DEBUG
#include "main.c"

void start(List(String) *args)
{
	if (listSize(String)(args) >= 2)		
		prints(
			addLast(char)(
				getElement(String)(args, 1),
				'\n'));
}
