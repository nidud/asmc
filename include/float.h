#ifndef __INC_FLOAT
#define __INC_FLOAT
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#define FLT_MAX		3.402823466e+38F
#define FLT_MAX_10_EXP	38
#define FLT_MAX_EXP	128
#define FLT_MIN		1.175494351e-38F
#define FLT_MIN_10_EXP	(-37)
#define FLT_MIN_EXP	(-125)
#define FLT_NORMALIZE	0
#define FLT_RADIX	2
#define FLT_ROUNDS	1

typedef float		REAL4;
typedef double		REAL8;
typedef long double	REAL10;

#ifdef __cplusplus
 }
#endif /* __cplusplus */
#endif /* __INC_FLOAT */
