#ifndef __INC_STRING
#define __INC_STRING
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void * _CType memcpy(void *, void *, size_t);
void * _CType memmove(void *, void *, size_t);
void * _CType memxchg(void *, void *, size_t);
void * _CType memset(void *, int, size_t);

int _CType memzero(void *, size_t);
int _CType memcmp(void *, void *, size_t);

size_t _CType strlen(char *);
char * _CType strcpy(char *, char *);
char * _CType strncpy(char *, char *, size_t);
char * _CType strcat(char *, char *);
char * _CType strncat(char *, char *, size_t);
int    _CType strcmp(char *, char *);
int    _CType strncmp(char *, char *, size_t);
int    _CType stricmp(char *, char *);
int    _CType strnicmp(char *, char *, size_t);
char * _CType strchr(char *, int);
char * _CType strrchr(char *, int);
char * _CType strstr(char *, char *);
char * _CType strupr(char *);
char * _CType strlwr(char *);
char * _CType strrev(char *);

char * _CType strfn(char *);
char * _CType strfcat(char *__dest, char *__path, char *__file);
char * _CType strstart(char *);
int    _CType strtrim(char *);
int    _CType cmpwarg(char *__file, char *__mask);
int    _CType cmpwargs(char *__file, char *__mask);
char * _CType unixtodos(char *);
char * _CType dostounix(char *);
char * _CType strxchg(void *__b, void *__old, void *__new, int __olen);
char * _CType atohex(char *);
char * _CType hextoa(char *);
long   _CType strtol(char *);
char * _CType setfext(char *, char *);
char * _CType argvext(char *__buf, char *__ext);

#ifdef __cplusplus
 }
#endif
#endif
