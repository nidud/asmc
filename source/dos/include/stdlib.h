#ifndef __INC_STDLIB
#define __INC_STDLIB
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

extern int doserrno;
extern int errno;
extern int sys_nerr;
extern char *sys_errlist[];
extern char *dos_errlist[];

void _CType exit(int);
long _CType atol(char *);
int  _CType atoi(char *);
long _CType xtol(char *);
long _CType strtol(char *);

char * _CType qwtostr(DWORD __high, DWORD __low);
char * _CType qwtobstr(DWORD __high, DWORD __low);
long _CType mkbstring(char *__buf, DWORD __high, DWORD __low);

char * _CType getenvp(char *);
char * _CType getenval(char *__buf, char *);
char * _CType expenviron(char *__string/*128*/);
char * _CType searchp(char *__program);
char * _CType searchpath(char *__file);

#ifdef __cplusplus
 }
#endif
#endif
