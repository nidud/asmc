ifndef __LIBC_INC
 include libc.inc
endif
ifndef _INC_QUADMATH
_INC_QUADMATH equ <>
.xlist

;; Function prototypes

PQFLOAT	    typedef ptr real16

acosq	    proto __cdecl :PQFLOAT
acoshq	    proto __cdecl :PQFLOAT
asinq	    proto __cdecl :PQFLOAT
asinhq	    proto __cdecl :PQFLOAT
atanq	    proto __cdecl :PQFLOAT
atanhq	    proto __cdecl :PQFLOAT
atan2q	    proto __cdecl :PQFLOAT, :PQFLOAT

cbrtq	    proto __cdecl :PQFLOAT
ceilq	    proto __cdecl :PQFLOAT
copysignq   proto __cdecl :PQFLOAT, :PQFLOAT
coshq	    proto __cdecl :PQFLOAT
cosq	    proto __cdecl :PQFLOAT
erfq	    proto __cdecl :PQFLOAT
erfcq	    proto __cdecl :PQFLOAT
expq	    proto __cdecl :PQFLOAT
expm1q	    proto __cdecl :PQFLOAT
fabsq	    proto __cdecl :PQFLOAT
fdimq	    proto __cdecl :PQFLOAT
finiteq	    proto __cdecl :PQFLOAT
floorq	    proto __cdecl :PQFLOAT
fmaq	    proto __cdecl :PQFLOAT, :PQFLOAT, :PQFLOAT
fmaxq	    proto __cdecl :PQFLOAT, :PQFLOAT
fminq	    proto __cdecl :PQFLOAT, :PQFLOAT
fmodq	    proto __cdecl :PQFLOAT, :PQFLOAT
frexpq	    proto __cdecl :PQFLOAT, :ptr
hypotq	    proto __cdecl :PQFLOAT, :PQFLOAT
isinfq	    proto __cdecl :PQFLOAT
ilogbq	    proto __cdecl :PQFLOAT
isnanq	    proto __cdecl :PQFLOAT
j0q	    proto __cdecl :PQFLOAT
j1q	    proto __cdecl :PQFLOAT
jnq	    proto __cdecl :SINT, :PQFLOAT
ldexpq	    proto __cdecl :PQFLOAT, :SINT
lgammaq	    proto __cdecl :PQFLOAT
llrintq	    proto __cdecl :PQFLOAT
llroundq    proto __cdecl :PQFLOAT
logbq	    proto __cdecl :PQFLOAT
logq	    proto __cdecl :PQFLOAT
log10q	    proto __cdecl :PQFLOAT
log2q	    proto __cdecl :PQFLOAT
log1pq	    proto __cdecl :PQFLOAT
lrintq	    proto __cdecl :PQFLOAT
lroundq	    proto __cdecl :PQFLOAT
modfq	    proto __cdecl :PQFLOAT, :PQFLOAT
nanq	    proto __cdecl :LPSTR
nearbyintq  proto __cdecl :PQFLOAT
nextafterq  proto __cdecl :PQFLOAT, :PQFLOAT
powq	    proto __cdecl :PQFLOAT, :PQFLOAT
remainderq  proto __cdecl :PQFLOAT, :PQFLOAT
remquoq	    proto __cdecl :PQFLOAT, :PQFLOAT, :ptr
rintq	    proto __cdecl :PQFLOAT
roundq	    proto __cdecl :PQFLOAT
scalblnq    proto __cdecl :PQFLOAT, :SINT
scalbnq	    proto __cdecl :PQFLOAT, :SINT
signbitq    proto __cdecl :PQFLOAT
sincosq	    proto __cdecl :PQFLOAT, :PQFLOAT, :PQFLOAT
sinhq	    proto __cdecl :PQFLOAT
sinq	    proto __cdecl :PQFLOAT
sqrtq	    proto __cdecl :PQFLOAT
tanq	    proto __cdecl :PQFLOAT
tanhq	    proto __cdecl :PQFLOAT
tgammaq	    proto __cdecl :PQFLOAT
truncq	    proto __cdecl :PQFLOAT
y0q	    proto __cdecl :PQFLOAT
y1q	    proto __cdecl :PQFLOAT
ynq	    proto __cdecl :SINT, :PQFLOAT

IsNaNq	    proto __cdecl :PQFLOAT
IsInfiniteq proto __cdecl :PQFLOAT
IsZeroq	    proto __cdecl :PQFLOAT

; Quadruple precision - binary128 -- REAL16 (__float128)

Q_SIGBITS   equ 113
Q_EXPBITS   equ 15
Q_EXPMASK   equ (1 shl Q_EXPBITS) - 1
Q_EXPBIAS   equ Q_EXPMASK shr 1
Q_EXPMAX    equ Q_EXPMASK - Q_EXPBIAS

; Quadruple precision constants

externdef   _Q_E:	REAL16 ; e
externdef   _Q_LOG2E:	REAL16 ; log2(e)
externdef   _Q_LOG10E:	REAL16 ; log10(e)
externdef   _Q_LN2:	REAL16 ; ln(2)
externdef   _Q_LN10:	REAL16 ; ln(10)
externdef   _Q_PI:	REAL16 ; pi
externdef   _Q_PI_2:	REAL16 ; pi/2
externdef   _Q_PI_4:	REAL16 ; pi/4
externdef   _Q_1_PI:	REAL16 ; 1/pi
externdef   _Q_2_PI:	REAL16 ; 2/pi
externdef   _Q_2_SQRTPI:REAL16 ; 2/sqrt(pi)
externdef   _Q_SQRT2:	REAL16 ; sqrt(2)
externdef   _Q_SQRT1_2: REAL16 ; 1/sqrt(2)
externdef   _Q_1E1:	REAL16 ; table..
externdef   _Q_1E2:	REAL16
externdef   _Q_1E4:	REAL16
externdef   _Q_1E8:	REAL16
externdef   _Q_1E16:	REAL16
externdef   _Q_1E32:	REAL16
externdef   _Q_1E64:	REAL16
externdef   _Q_1E128:	REAL16
externdef   _Q_1E256:	REAL16
externdef   _Q_1E512:	REAL16
externdef   _Q_1E1024:	REAL16
externdef   _Q_1E2048:	REAL16
externdef   _Q_1E4096:	REAL16
externdef   _Q_INF:	REAL16
externdef   _Q_INF_M:	REAL16
externdef   _Q_ZERO:	REAL16
externdef   _Q_NAN:	REAL16
externdef   _Q_ONE:	REAL16

_mulfq	proto __cdecl :ptr, :ptr, :ptr
_divfq	proto __cdecl :ptr, :ptr, :ptr
_addfq	proto __cdecl :ptr, :ptr, :ptr
_subfq	proto __cdecl :ptr, :ptr, :ptr

.list
endif ;; _INC_QUADMATH

