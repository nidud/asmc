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
extern int _argc;
extern char **_argv;
extern char **_environ;

_CRTIMP void	_CType abort(void);
_CRTIMP void	_CType exit(int);
_CRTIMP int	_CType atoi(const char *);
_CRTIMP long	_CType atol(const char *);
_CRTIMP __int64 _CType _atoi64(const char *);
_CRTIMP char *	_CType getenv(const char *);
_CRTIMP void	_CType qsort(void *, size_t, size_t, int (_CType *)(const void *, const void *));
_CRTIMP char *	_CType _fullpath(char *, const char *, size_t);
_CRTIMP double	_CType strtod(const char *, char **);
_CRTIMP void *	_CType malloc(size_t);
_CRTIMP void *	_CType realloc(void *, size_t);
_CRTIMP void *	_CType calloc(size_t, size_t);
_CRTIMP void	_CType free(void *);
_CRTIMP int	_CType system(const char *);

long	_CType xtol(const char *);

#ifdef __cplusplus
 }
#endif
#endif
