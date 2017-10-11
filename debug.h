#ifndef DEBUG_H
#define DEBUG_H


#include <stdio.h>
#include <execinfo.h>
#include <signal.h>

void die(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
#ifdef DEBUG
	int size = 10000;
	void *buffer[size];
	size = backtrace(buffer, size);
	backtrace_symbols_fd(buffer, size, 2);
#endif
	exit(1);
}

void segv_handler()
{
	fputs("Segmentation fault", stderr);
	fputc('\n', stderr);
#ifdef DEBUG
	int size = 10000;
	void *buffer[size];
	size = backtrace(buffer, size);
	backtrace_symbols_fd(buffer, size, 2);
#endif
	abort();
}


#endif
