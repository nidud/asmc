#ifndef _MEMALLOC_H_
#define _MEMALLOC_H_

#include <malloc.h>

void *	FASTCALL MemAlloc(size_t);
void *	FASTCALL LclAlloc(size_t);
void	MemInit(void);
void	MemFini(void);

#define MemFree(m) free(m)
#define myalloca   alloca
#define LclFree( p )

#endif
