#ifndef __INC_STRING
#define __INC_STRING
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

_CRTIMP void *	__cdecl memcpy(void *, const void *, size_t);
_CRTIMP int	__cdecl memcmp(const void *, const void *, size_t);
_CRTIMP void *	__cdecl memset(void *, int, size_t);
_CRTIMP void *	__cdecl memchr(const void *, int, size_t);
_CRTIMP void *	__cdecl memmove(void *, const void *, size_t);
_CRTIMP char *	__cdecl strcpy(char *, const char *);
_CRTIMP char *	__cdecl strcat(char *, const char *);
_CRTIMP int	__cdecl strcmp(const char *, const char *);
_CRTIMP size_t	__cdecl strlen(const char *);
_CRTIMP char *	__cdecl strchr(const char *, int);
_CRTIMP int	__cdecl strncmp(const char *, const char *, size_t);
_CRTIMP char *	__cdecl strncpy(char *, const char *, size_t);
_CRTIMP char *	__cdecl strrchr(const char *, int);
_CRTIMP char *	__cdecl strstr(const char *, const char *);
_CRTIMP char *	__cdecl strtok(char *, const char *);

#ifndef __GNUC__
_CRTIMP void *	__cdecl _memcpy(void *, const void *, size_t);
_CRTIMP int	__cdecl _memicmp(const void *, const void *, size_t);
_CRTIMP int	__cdecl _stricmp(const char *, const char *);
_CRTIMP char *	__cdecl _strlwr(char *);
_CRTIMP int	__cdecl _strnicmp(const char *, const char *, size_t);
_CRTIMP char *	__cdecl _strrev(char *);
_CRTIMP char *	__cdecl _strupr(char *);
#endif
#ifndef NO_OLDNAMES
char *	__cdecl strdup(const char *);
int	__cdecl strcmpi(const char *, const char *);
int	__cdecl stricmp(const char *, const char *);
char *	__cdecl strlwr(char *);
int	__cdecl strnicmp(const char *, const char *, size_t);
int	__cdecl strncasecmp(const char *, const char *, size_t);
int	__cdecl strcasecmp(const char *, const char *);
char *	__cdecl strnset(char *, int, size_t);
char *	__cdecl strrev(char *);
char *	__cdecl strset(char *, int);
char *	__cdecl strupr(char *);
#else
#define stricmp	 _stricmp
#define strnicmp _strnicmp
#endif

#define memzero(s,z) memset(s,0,z)

#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED
_CRTIMP short * __cdecl wcscat(short *, short *);
_CRTIMP int	__cdecl wcslen(short *);
_CRTIMP short * __cdecl wcschr(short *, int);
_CRTIMP int	__cdecl wcscmp(short *, short *);
_CRTIMP short * __cdecl wcscpy(short *, short *);
_CRTIMP short * __cdecl wcsstr(short *, short *);
_CRTIMP short * __cdecl wcstok(short *, short *);
_CRTIMP short * __cdecl wcsncpy(short *, short *, size_t);
_CRTIMP int	__cdecl wcsncmp(short *, short *, size_t);
_CRTIMP short * __cdecl wcsncat(short *, short *, size_t);
_CRTIMP short * __cdecl wcsrchr(short *, int);
_CRTIMP short * __cdecl wcspbrk(short *, short *);
#endif

void *	__cdecl memxchg(void *, void *, size_t);
char *	__cdecl strfn(const char *);
char *	__cdecl strfcat(char *, const char *, const char *);
char *	__cdecl setfext(char *, const char *);
char *	__cdecl strext(const char *);
int	__cdecl strtrim(char *);
char *	__cdecl strstart(const char *);

#ifdef __cplusplus
 }
#endif
#endif
