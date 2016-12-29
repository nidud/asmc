#ifndef __INC_STDDEF
#define __INC_STDDEF
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#define __size(x)	((sizeof(x) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(ap,p)	(ap = (va_list)&p + __size(p))
#define va_arg(ap,t)	(*(t *)((ap += __size(t)) - __size(t)))
#define va_end(ap)	(ap = (va_list)0)

#ifdef __cplusplus
 }
#endif
#endif
