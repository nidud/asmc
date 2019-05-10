#ifndef QUADMATH_H
#define QUADMATH_H
#ifndef _INTTYPE_H_INCLUDED_
#include <inttype.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
     uint_64		u64[2];
     unsigned int	u32[4];
     unsigned short	u16[8];
     unsigned char	u8[16];
 } U128;

extern U128 _Q_E;	/* e */
extern U128 _Q_LOG2E;	/* log2(e) */
extern U128 _Q_LOG10E;	/* log10(e) */
extern U128 _Q_LN2;	/* ln(2) */
extern U128 _Q_LN10;	/* ln(10) */
extern U128 _Q_PI;	/* pi */
extern U128 _Q_PI_2;	/* pi/2 */
extern U128 _Q_PI_4;	/* pi/4 */
extern U128 _Q_1_PI;	/* 1/pi */
extern U128 _Q_2_PI;	/* 2/pi */
extern U128 _Q_2_SQRTPI;/* 2/sqrt(pi) */
extern U128 _Q_SQRT2;	/* sqrt(2) */
extern U128 _Q_SQRT1_2; /* 1/sqrt(2) */
extern U128 _Q_NAN;
extern U128 _Q_ONE;
extern U128 _Q_ZERO;
extern U128 _Q_INF_M;
extern U128 _Q_1E1;	/* table.. */
extern U128 _Q_1E2;
extern U128 _Q_1E4;
extern U128 _Q_1E8;
extern U128 _Q_1E16;
extern U128 _Q_1E32;
extern U128 _Q_1E64;
extern U128 _Q_1E128;
extern U128 _Q_1E256;
extern U128 _Q_1E512;
extern U128 _Q_1E1024;
extern U128 _Q_1E2048;
extern U128 _Q_1E4096;
extern U128 _Q_INF;

#ifdef _WIN64

void *	__mulq(void *, void *);
void *	__divq(void *, void *);
void *	__addq(void *, void *);
void *	__subq(void *, void *);
void *	__cvtq_h(void *, void *);
void *	__cvtq_ss(void *, void *);
void *	__cvtq_sd(void *, void *);
void *	__cvtq_ld(void *, void *);
void *	__cvth_q(void *, void *);
void *	__cvtss_q(void *, void *);
void *	__cvtsd_q(void *, void *);
void *	__cvtld_q(void *, void *);
void *	__cvti32_q(void *, int);
void *	__cvti64_q(void *, int_64);
int	__cvtq_i32(void *);
int_64	__cvtq_i64(void *);
int	__cvta_q(void *, const char *, char **);

#define mulq	 __mulq
#define divq	 __divq
#define addq	 __addq
#define subq	 __subq
#define cvtq_h	 __cvtq_h
#define cvtq_ss	 __cvtq_ss
#define cvtq_sd	 __cvtq_sd
#define cvtq_ld	 __cvtq_ld
#define cvth_q	 __cvth_q
#define cvtss_q	 __cvtss_q
#define cvtsd_q	 __cvtsd_q
#define cvtld_q	 __cvtld_q
#define cvti32_q __cvti32_q
#define cvti64_q __cvti64_q
#define cvtq_i32 __cvtq_i32
#define cvtq_i64 __cvtq_i64
#define cvta_q	 __cvta_q

#else

void *	mulq(void *, void *);
void *	divq(void *, void *);
void *	addq(void *, void *);
void *	subq(void *, void *);
void *	cvtq_h(void *, void *);
void *	cvtq_ss(void *, void *);
void *	cvtq_sd(void *, void *);
void *	cvtq_ld(void *, void *);
void *	cvth_q(void *, void *);
void *	cvtss_q(void *, void *);
void *	cvtsd_q(void *, void *);
void *	cvtld_q(void *, void *);
void *	cvti32_q(void *, int);
void *	cvti64_q(void *, int_64);
int	cvtq_i32(void *);
int_64	cvtq_i64(void *);
int	cvta_q(void *, const char *, char **);

#endif

#ifdef __cplusplus
}
#endif
#endif
