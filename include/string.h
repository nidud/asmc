#ifndef __INC_STRING
#define __INC_STRING
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

_CRTIMP void *	_CType memcpy(void *, const void *, size_t);
_CRTIMP int	_CType memcmp(const void *, const void *, size_t);
_CRTIMP void *	_CType memset(void *, int, size_t);
_CRTIMP char *	_CType strcpy(char *, const char *);
_CRTIMP char *	_CType strcat(char *, const char *);
_CRTIMP int	_CType strcmp(const char *, const char *);
_CRTIMP size_t	_CType strlen(const char *);
_CRTIMP void *	_CType memchr(const void *, int, size_t);
_CRTIMP void *	_CType memmove(void *, const void *, size_t);
_CRTIMP int	_CType _memicmp(const void *, const void *, size_t);
_CRTIMP char *	_CType strchr(const char *, int);
_CRTIMP int	_CType _stricmp(const char *, const char *);
_CRTIMP char *	_CType _strlwr(char *);
_CRTIMP int	_CType strncmp(const char *, const char *, size_t);
_CRTIMP int	_CType _strnicmp(const char *, const char *, size_t);
_CRTIMP char *	_CType strncpy(char *, const char *, size_t);
_CRTIMP char *	_CType strrchr(const char *, int);
_CRTIMP char *	_CType _strrev(char *);
_CRTIMP char *	_CType strstr(const char *, const char *);
_CRTIMP char *	_CType _strupr(char *);
_CRTIMP char *	_CType strtok(char *, const char *);

#define memzero(s,z) memset(s,0,z)

#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED
_CRTIMP short * _CType wcscat(short *, short *);
_CRTIMP int	_CType wcslen(short *);
_CRTIMP short * _CType wcschr(short *, int);
_CRTIMP int	_CType wcscmp(short *, short *);
_CRTIMP short * _CType wcscpy(short *, short *);
_CRTIMP short * _CType wcsstr(short *, short *);
_CRTIMP short * _CType wcstok(short *, short *);
_CRTIMP short * _CType wcsncpy(short *, short *, size_t);
_CRTIMP int	_CType wcsncmp(short *, short *, size_t);
_CRTIMP short * _CType wcsncat(short *, short *, size_t);
_CRTIMP short * _CType wcsrchr(short *, int);
_CRTIMP short * _CType wcspbrk(short *, short *);
#endif

void *	_CType memxchg(void *, void *, size_t);
char *	_CType strfn(const char *);
char *	_CType strfcat(char *, const char *, const char *);
char *	_CType setfext(char *, const char *);
char *	_CType strext(const char *);

#define stricmp	 _stricmp
#define strnicmp _strnicmp

#ifdef __cplusplus
 }
#endif
#endif
