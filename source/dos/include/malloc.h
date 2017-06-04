#ifndef __INC_MALLOC
#define __INC_MALLOC
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

void _CType free(void *__block);
void *_CType malloc(size_t __size);

#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
extern char huge * __cdecl heapbase;
extern char huge * __cdecl heaptop;
extern char huge * __cdecl brklvl;
long _CType coreleft(void);
#else
int _CType coreleft(void);
#endif

#define EMMPAGE 0x4000

int	_CType emminit(void);		/* error = 0  */
int	_CType emmversion(void);
int	_CType emmalloc(int __pages);	/* error = -1 */
int	_CType emmfree(int __handle);
DWORD	_CType emmcoreleft(void);
int	_CType emmnumfreep(void);
WORD	_CType emmgetseg(void);
int	_CType emmread(void *, int __handle, int __page);
int	_CType emmwrite(void *, int __handle, int __page);

#ifdef __cplusplus
 }
#endif
#endif /* __INC_MALLOC */
