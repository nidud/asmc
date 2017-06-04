#ifndef __INC_SETJMP
#define __INC_SETJMP
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef _WIN64
#define _JBLEN	10
#define _JBTYPE QWORD
#else
#define _JBLEN	8
#define _JBTYPE DWORD
#endif
typedef _JBTYPE jmp_buf[_JBLEN];

int  __cdecl setjmp(jmp_buf);
void __cdecl longjmp(jmp_buf, int);

#ifdef __cplusplus
 }
#endif /* __cplusplus */
#endif /* __INC_SETJMP */

