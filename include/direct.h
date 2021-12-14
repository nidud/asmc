#ifndef __INC_DIRECT
#define __INC_DIRECT
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

_CRTIMP int __cdecl _chdir(char *);
_CRTIMP int __cdecl _chdrive(int);
_CRTIMP char * __cdecl _getcwd(char *, int);
_CRTIMP char * __cdecl _getdcwd(int __drive, char *__pnbuf, int __maxlen);
_CRTIMP int __cdecl _mkdir(char *);
_CRTIMP int __cdecl _rmdir(char *);
_CRTIMP int __cdecl _getdrive(void);
_CRTIMP unsigned long __cdecl _getdrives(void);
_CRTIMP int __cdecl _wchdir(const wchar_t *);
_CRTIMP wchar_t * __cdecl _wgetcwd(wchar_t *, int);
_CRTIMP wchar_t * __cdecl _wgetdcwd(int, wchar_t *, int);
_CRTIMP int __cdecl _wmkdir(const wchar_t *);
_CRTIMP int __cdecl _wrmdir(const wchar_t *);

/**/

char * __cdecl wlongpath(const char *__path, const char *__file);
char * __cdecl wlongname(const char *__path, const char *__file);

#ifdef __cplusplus
 }
#endif
#endif
