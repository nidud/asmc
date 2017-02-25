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

_CRTIMP void	_CType abort(void);
_CRTIMP void	_CType exit(int);
_CRTIMP int	_CType atoi(const char *);
_CRTIMP long	_CType atol(const char *);
_CRTIMP __int64 _CType _atoi64(const char *);
_CRTIMP char *	_CType getenv(const char *);
_CRTIMP int	_CType mbtowc(wchar_t *, const char *, size_t);
_CRTIMP size_t	_CType mbstowcs(wchar_t *, const char *, size_t);
_CRTIMP void	_CType qsort(void *, size_t, size_t, int (_CType *)(const void *, const void *));
_CRTIMP char *	_CType _fullpath(char *, const char *, size_t);
_CRTIMP double	_CType strtod(const char *, char **);
_CRTIMP void *	_CType malloc(size_t);
_CRTIMP void *	_CType realloc(void *, size_t);
_CRTIMP void *	_CType calloc(size_t, size_t);
_CRTIMP void	_CType free(void *);
_CRTIMP int	_CType system(const char *);

long	_CType xtol(const char *);

#ifndef _WSTDLIB_DEFINED

_CRTIMP int	_CType _wtoi(const wchar_t *);
_CRTIMP long	_CType _wtol(const wchar_t *);
_CRTIMP double	_CType wcstod(const wchar_t *, wchar_t **);
_CRTIMP int	_CType _wsystem(const wchar_t *);
_CRTIMP wchar_t * _CType _wgetenv(const wchar_t *);

#define _WSTDLIB_DEFINED
#endif

#ifdef __cplusplus
 }
#endif
#endif
