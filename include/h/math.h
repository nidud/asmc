#ifndef __INC_MATH
#define __INC_MATH
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define FP_INFINITE	1
#define FP_NAN		2
#define FP_NORMAL	(-1)
#define FP_SUBNORMAL	(-2)
#define FP_ZERO		0

#define FP_ILOGB0	(-0x7fffffff - 1)
#define FP_ILOGBNAN	0x7fffffff

#define MATH_ERRNO	1
#define MATH_ERREXCEPT	2

#define _FP_LT		1
#define _FP_EQ		2
#define _FP_GT		4

#define _DOMAIN		1
#define _SING		2
#define _OVERFLOW	3
#define _UNDERFLOW	4
#define _TLOSS		5
#define _PLOSS		6

#ifdef __cplusplus
 extern "C" {
#endif
#ifdef __cplusplus
 }
#endif
#endif /* __INC_MATH */
