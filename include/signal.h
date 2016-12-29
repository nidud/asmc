#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef void _CType __sigfunc(int);

#define SIGINT	2
#define SIGILL	4
#define SIGABRT 6
#define SIGFPE	8
#define SIGSEGV 11
#define SIGTERM 15

int _CType raise(int);
__sigfunc * _CType signal(int, __sigfunc *);

#endif

