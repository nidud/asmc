#ifndef QUADMATH_H
#define QUADMATH_H
#ifndef _INTTYPE_H_INCLUDED_
#include <inttype.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

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
