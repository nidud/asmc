#ifndef __QFLAOT_H
#define __QFLOAT_H
#ifndef _INTTYPE_H_INCLUDED_
#include <inttype.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/* Half precision - binary16 -- REAL2 (half) */

#define H_SIGBITS	11
#define H_EXPBITS	5
#define H_EXPMASK	((1 << H_EXPBITS) - 1)
#define H_EXPBIAS	(H_EXPMASK >> 1)
#define H_EXPMAX	(H_EXPMASK - H_EXPBIAS)

/* Single precision - binary32 -- REAL4 (float) */

#define F_SIGBITS	24
#define F_EXPBITS	8
#define F_EXPMASK	((1 << F_EXPBITS) - 1)
#define F_EXPBIAS	(F_EXPMASK >> 1)
#define F_EXPMAX	(F_EXPMASK - F_EXPBIAS)

/* Double precision - binary64 -- REAL8 (double) */

#define D_SIGBITS	53
#define D_EXPBITS	11
#define D_EXPMASK	((1 << D_EXPBITS) - 1)
#define D_EXPBIAS	(D_EXPMASK >> 1)
#define D_EXPMAX	(D_EXPMASK - D_EXPBIAS)

/* Long Double precision - binary80 -- REAL10 (long double) */

#define LD_SIGBITS	64
#define LD_EXPBITS	15
#define LD_EXPMASK	((1 << LD_EXPBITS) - 1)
#define LD_EXPBIAS	(LD_EXPMASK >> 1)
#define LD_EXPMAX	(LD_EXPMASK - LD_EXPBIAS)

/* Quadruple precision - binary128 -- real16 (__float128) */

#define Q_SIGBITS	113
#define Q_EXPBITS	15
#define Q_EXPMASK	((1 << Q_EXPBITS) - 1)
#define Q_EXPBIAS	(Q_EXPMASK >> 1)
#define Q_EXPMAX	(Q_EXPMASK - Q_EXPBIAS)

typedef struct { /* extended (134-bit, 128+16) float */
    uint_64 l;
    uint_64 h;
    short e;
  } EXTFLOAT;

typedef struct {
    EXTFLOAT q;
    int flags;	  /* parsing flags */
    int exponent; /* exponent of floating point number */
    char *string; /* pointer to buffer or string */
   } STRFLT;

extern EXTFLOAT _fltpowtable[];

EXTFLOAT *_fltscale(EXTFLOAT *, int);

EXTFLOAT *_fltunpack(EXTFLOAT *, EXTFLOAT *);
EXTFLOAT *_fltpackfp(EXTFLOAT *, EXTFLOAT *);

EXTFLOAT *_fltadd(EXTFLOAT *, EXTFLOAT *);
EXTFLOAT *_fltsub(EXTFLOAT *, EXTFLOAT *);
EXTFLOAT *_fltdiv(EXTFLOAT *, EXTFLOAT *);
EXTFLOAT *_fltmul(EXTFLOAT *, EXTFLOAT *);

int	__cmpq(void *, void *);
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

void *	__addo(void *, void *);
void *	__subo(void *, void *);
void *	__mulo(void *, void *, void *);
void *	__divo(void *, void *, void *);
void *	__shlo(void *, int, int);
void *	__shro(void *, int, int);
void *	__saro(void *, int, int);

#ifdef __cplusplus
}
#endif
#endif
