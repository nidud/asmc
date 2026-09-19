
; v2.39.13 -- allow macro expansion in vector assignment

define F 0.159154943
define D <{ F, F }>
define S <{ F, F, F, F }>
define X xmm0
define Y xmm1

_mm_mul_ps macro a, b
    mulps a,b
    retm<a>
    endm

_mm_mul_pd macro a, b
    mulpd a,b
    retm<a>
    endm

.code
 _mm_mul_ps(X, _mm_mul_ps(Y, S))
 _mm_mul_pd(X, _mm_mul_pd(Y, D))
 end

