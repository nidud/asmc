#ifndef _MEMALLOC_H_
#define _MEMALLOC_H_

void *	FASTCALL MemAlloc(size_t);
void *	FASTCALL LclAlloc(size_t);
void	MemInit(void);
void	MemFini(void);

#define MemFree(m) free(m)
#define LclFree(p)

#if defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__OCC__)
#define myalloca  alloca
#include <malloc.h>
#elif defined(__GNUC__) || defined(__TINYC__)
#define alloca(x) __builtin_alloca(x)
#define myalloca alloca
#ifndef __FreeBSD__  /* added v2.08 */
#include <malloc.h>  /* added v2.07 */
#endif
#elif defined(__PCC__)
#define myalloca  _alloca
#include <malloc.h>
#else
#define myalloca _alloca
#endif

#endif
