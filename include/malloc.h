#ifndef __INC_MALLOC
#define __INC_MALLOC
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _HEAP_GROWSIZE 0x10000

#ifdef __cplusplus
 extern "C" {
#endif

_CRTIMP void *	_CType malloc(size_t);
_CRTIMP void *	_CType realloc(void *, size_t);
_CRTIMP void *	_CType calloc(size_t, size_t);
_CRTIMP void	_CType free(void *);

void * _CType alloca(size_t);
void * _CType salloc(const char *);
void * _CType _aligned_malloc(size_t, int);
void * _CType _alloca64(size_t, int);

extern unsigned int _amblksiz;

#define _alloca alloca

#ifdef __cplusplus
 }
#endif
#endif /* __INC_MALLOC */
