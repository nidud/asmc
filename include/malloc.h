#ifndef __INC_MALLOC
#define __INC_MALLOC
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _HEAP_GROWSIZE 0x10000

#ifdef __cplusplus
 extern "C" {
#endif

_CRTIMP void *	__cdecl malloc(size_t);
_CRTIMP void *	__cdecl realloc(void *, size_t);
_CRTIMP void *	__cdecl calloc(size_t, size_t);
_CRTIMP void	__cdecl free(void *);

void * __cdecl alloca(size_t);
void * __cdecl salloc(const char *);
void * __cdecl _aligned_malloc(size_t, int);
void * __cdecl _alloca64(size_t, int);

extern unsigned int _amblksiz;

#define _alloca alloca

#ifdef __cplusplus
 }
#endif
#endif /* __INC_MALLOC */
