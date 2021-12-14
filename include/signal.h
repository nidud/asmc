#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef void __cdecl __sigfunc(int);

#define SIGINT		2
#define SIGILL		4
#define SIGABRT		6
#define SIGFPE		8
#define SIGSEGV		11
#define SIGTERM		15
#define SIGBREAK	21

int __cdecl raise(int);
__sigfunc * __cdecl signal(int, __sigfunc *);

#endif

