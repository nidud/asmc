#ifndef __INC_STDDEF
#define __INC_STDDEF
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#define offsetof(s,m)	(size_t)&(((s *)0)->m)

#ifdef __cplusplus
 }
#endif
#endif
