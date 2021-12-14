#ifndef __INC_STDDEF
#define __INC_STDDEF
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__CYGWIN__)
#define offsetof(s,m) __builtin_offsetof(s,m)
#else
#define offsetof(s,m) (size_t)&(((s *)0)->m)
#endif

#ifdef __cplusplus
 }
#endif
#endif
