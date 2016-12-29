#ifndef _MEMALLOC_H_
#define _MEMALLOC_H_

#include <malloc.h>

void *	__fastcall MemAlloc(size_t);
void *	__fastcall LclAlloc(size_t);
void	__stdcall  MemInit(void);
void	__stdcall  MemFini(void);

#define MemFree(m) free(m)
#define myalloca   alloca

#endif
