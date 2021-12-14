#ifndef __INC_STDLIB
#define __INC_STDLIB
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _MAX_PATH   260
#define _MAX_DRIVE  3
#define _MAX_DIR    256
#define _MAX_FNAME  256
#define _MAX_EXT    256

#ifdef __cplusplus
 extern "C" {
#endif

extern int errno;
extern int oserrno;
extern int sys_nerr;
extern char *sys_errlist[];

_CRTIMP extern int __argc;
_CRTIMP extern char **__argv;
_CRTIMP extern char **_environ;
_CRTIMP extern char *_pgmptr;
_CRTIMP extern wchar_t **__wargv;
_CRTIMP extern wchar_t **_wenviron;
_CRTIMP extern wchar_t *_wpgmptr;

_CRTIMP void	__cdecl abort(void);
_CRTIMP void	__cdecl exit(int);
_CRTIMP int	__cdecl atoi(const char *);
_CRTIMP long	__cdecl atol(const char *);
_CRTIMP __int64 __cdecl _atoi64(const char *);
_CRTIMP char *	__cdecl getenv(const char *);
_CRTIMP int	__cdecl mbtowc(wchar_t *, const char *, size_t);
_CRTIMP size_t	__cdecl mbstowcs(wchar_t *, const char *, size_t);
_CRTIMP void	__cdecl qsort(void *, size_t, size_t, int (*)(const void *, const void *));
_CRTIMP char *	__cdecl _fullpath(char *, const char *, size_t);
_CRTIMP double	__cdecl strtod(const char *, char **);
_CRTIMP void *	__cdecl malloc(size_t);
_CRTIMP void *	__cdecl realloc(void *, size_t);
_CRTIMP void *	__cdecl calloc(size_t, size_t);
_CRTIMP void	__cdecl free(void *);
_CRTIMP int	__cdecl system(const char *);

void *	__cdecl _strtoq(void *, const char *, char **);
long	__cdecl __xtol(const char *);

#ifndef _WSTDLIB_DEFINED

_CRTIMP int	__cdecl _wtoi(const wchar_t *);
_CRTIMP long	__cdecl _wtol(const wchar_t *);
_CRTIMP double	__cdecl wcstod(const wchar_t *, wchar_t **);
_CRTIMP int	__cdecl _wsystem(const wchar_t *);
_CRTIMP wchar_t * __cdecl _wgetenv(const wchar_t *);

#define _WSTDLIB_DEFINED
#endif

#ifdef __cplusplus
 }
#endif
#endif
