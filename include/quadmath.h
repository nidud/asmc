#ifndef QUADMATH_H
#define QUADMATH_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef int_64
#if defined(LONG_IS_64BITS) || defined(__LP64__)
typedef signed long int_64;
typedef signed long uint_64;
#elseif defined(LLONG_MAX) || defined(__GNUC__)
typedef signed long long int_64;
typedef unsigned long long uint_64;
#else
typedef signed __int64 int_64;
typedef unsigned __int64 uint_64;
#endif
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

#define ERANGE 34

extern int qerrno;

void *	quadmul(void *, void *);
void *	quaddiv(void *, void *);
void *	quadadd(void *, void *);
void *	quadsub(void *, void *);
void *	quadtof(void *, void *);
void *	quadtod(void *, void *);
void *	quadtold(void *, void *);
void *	ftoquad(void *, void *);
void *	dtoquad(void *, void *);
void *	ldtoquad(void *, void *);
void *	i32toquad(void *, int);
void *	i64toquad(void *, int_64);
int	quadtoi32(void *);
int_64	quadtoi64(void *);
int	atoquad(void *, const char *, char **);
int	quadisinf(void *);
int	quadisnan(void *);

#ifdef __cplusplus
}
#endif
#endif
