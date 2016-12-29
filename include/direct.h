#ifndef __INC_DIRECT
#define __INC_DIRECT
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

_CRTIMP int _CType _chdir(char *);
_CRTIMP int _CType _chdrive(int);
_CRTIMP char * _CType _getcwd(char *, int);
_CRTIMP char * _CType _getdcwd(int __drive, char *__pnbuf, int __maxlen);
_CRTIMP int _CType _mkdir(char *);
_CRTIMP int _CType _rmdir(char *);
_CRTIMP int _CType _getdrive(void);
_CRTIMP DWORD _CType _getdrives(void);

_CRTIMP int _CType _wchdir(const wchar_t *);
_CRTIMP wchar_t * _CType _wgetcwd(wchar_t *, int);
_CRTIMP wchar_t * _CType _wgetdcwd(int, wchar_t *, int);
_CRTIMP int _CType _wmkdir(const wchar_t *);
_CRTIMP int _CType _wrmdir(const wchar_t *);

#ifdef __cplusplus
 }
#endif
#endif
