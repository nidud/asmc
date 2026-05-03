#ifndef __INC_STDDEF
#define __INC_STDDEF
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#define _ADDRESSOF(v)	( &(v) )

#if defined (_M_IX86)

#define _INTSIZEOF(n)	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)	( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define va_arg(ap,t)	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)	( ap = (va_list)0 )

#elif defined (_M_X64)

extern void __cdecl __va_start(va_list *, ...);
#define va_start(ap, x) ( __va_start(&ap, x) )
#define va_arg(ap, t)	\
    ( ( sizeof(t) > sizeof(__int64) || ( sizeof(t) & (sizeof(t) - 1) ) != 0 ) \
	? **(t **)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) \
	:  *(t	*)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) )
#define va_end(ap)	( ap = (va_list)0 )

#else

#define _INTSIZEOF(n)	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)	( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define va_arg(ap,t)	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)	( ap = (va_list)0 )

#endif

#ifdef __cplusplus
 }
#endif
#endif
