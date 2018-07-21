ifndef _INC_QUADMATH
_INC_QUADMATH equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

if 0
ifdef __PE__
option dllimport:<quadmath>
else
includelib quadmath.lib
endif
endif

_ST_SIGN	equ 0x0001
_ST_NEGNUM	equ 0x0002
_ST_NEGEXP	equ 0x0004
_ST_ISZERO	equ 0x0008
_ST_ISHEX	equ 0x0010
_ST_ISNAN	equ 0x0020
_ST_ISINF	equ 0x0040
_ST_INVALID	equ 0x0080
_ST_UNDERFLOW	equ 0x0100
_ST_OVERFLOW	equ 0x0200
_ST_DIGITS	equ 0x0400
_ST_DOT		equ 0x0800

; Single precision - binary32 -- REAL4 (float)

F_SIGBITS	equ 24
F_EXPBITS	equ 8
F_EXPMASK	equ (1 shl F_EXPBITS) - 1
F_EXPBIAS	equ F_EXPMASK shr 1
F_EXPMAX	equ F_EXPMASK - F_EXPBIAS

; Double precision - binary64 -- REAL8 (double)

D_SIGBITS	equ 53
D_EXPBITS	equ 11
D_EXPMASK	equ (1 shl D_EXPBITS) - 1
D_EXPBIAS	equ D_EXPMASK shr 1
D_EXPMAX	equ D_EXPMASK - D_EXPBIAS

; Long Double precision - binary80 -- REAL10 (long double)

LD_SIGBITS	equ 64
LD_EXPBITS	equ 15
LD_EXPMASK	equ (1 shl LD_EXPBITS) - 1
LD_EXPBIAS	equ LD_EXPMASK shr 1
LD_EXPMAX	equ LD_EXPMASK - LD_EXPBIAS

; Quadruple precision - binary128 -- REAL16 (__float128)

Q_SIGBITS	equ 113
Q_EXPBITS	equ 15
Q_EXPMASK	equ (1 shl Q_EXPBITS) - 1
Q_EXPBIAS	equ Q_EXPMASK shr 1
Q_EXPMAX	equ Q_EXPMASK - Q_EXPBIAS

.pragma pack(push,1)

U128 UNION
    f		real4 ?
    d		real8 ?
    ld		real10 ?
    STRUC
	ldm	dq ?
	lde	dw ?
    ENDS
    STRUC
	qmw	dw ?
	qmd	dd ?
	qmh	dq ?
	e	dw ?
    ENDS
    m8		db 16 dup(?)
    m16		dw 8 dup(?)
    m32		dd 4 dup(?)
    m64		dq 2 dup(?)
U128 ENDS

U256 UNION
    m8		db 32 dup(?)
    m16		dw 16 dup(?)
    m32		dd 8 dup(?)
    m64		dq 4 dup(?)
U256 ENDS

.pragma pack(pop)

ifdef _LINUX
PU128 typedef size_t
PU256 typedef size_t
else
PU128 typedef ptr U128
PU256 typedef ptr U256
endif

XQFLOAT		typedef REAL16
PQFLOAT		typedef ptr REAL16

quadmul		proto __cdecl :ptr, :ptr
quaddiv		proto __cdecl :ptr, :ptr
quadadd		proto __cdecl :ptr, :ptr
quadsub		proto __cdecl :ptr, :ptr
quadisinf	proto __cdecl :ptr
quadisnan	proto __cdecl :ptr
quadtof		proto __cdecl :ptr, :ptr
quadtod		proto __cdecl :ptr, :ptr
quadtold	proto __cdecl :ptr, :ptr
ftoquad		proto __cdecl :ptr, :ptr
dtoquad		proto __cdecl :ptr, :ptr
ldtoquad	proto __cdecl :ptr, :ptr

quadtoi32	proto __cdecl :ptr
quadtoi64	proto __cdecl :ptr
i32toquad	proto __cdecl :ptr, :sdword
i64toquad	proto __cdecl :ptr, :sqword

atoquad		proto __cdecl :ptr, :LPSTR, :ptr LPSTR
strtoflt128	proto __cdecl :LPSTR, :ptr LPSTR
quadnormalize	proto __cdecl :ptr, :SINT

_udiv256	proto __cdecl :PU256, :PU256, :PU256
_mul256		proto __cdecl :PU128, :PU128, :PU128

; Quadruple precision constants

externdef   _Q_E:	XQFLOAT ; e
externdef   _Q_LOG2E:	XQFLOAT ; log2(e)
externdef   _Q_LOG10E:	XQFLOAT ; log10(e)
externdef   _Q_LN2:	XQFLOAT ; ln(2)
externdef   _Q_LN10:	XQFLOAT ; ln(10)
externdef   _Q_PI:	XQFLOAT ; pi
externdef   _Q_PI_2:	XQFLOAT ; pi/2
externdef   _Q_PI_4:	XQFLOAT ; pi/4
externdef   _Q_1_PI:	XQFLOAT ; 1/pi
externdef   _Q_2_PI:	XQFLOAT ; 2/pi
externdef   _Q_2_SQRTPI:XQFLOAT ; 2/sqrt(pi)
externdef   _Q_SQRT2:	XQFLOAT ; sqrt(2)
externdef   _Q_SQRT1_2: XQFLOAT ; 1/sqrt(2)
externdef   _Q_1E1:	XQFLOAT ; table..
externdef   _Q_1E2:	XQFLOAT
externdef   _Q_1E4:	XQFLOAT
externdef   _Q_1E8:	XQFLOAT
externdef   _Q_1E16:	XQFLOAT
externdef   _Q_1E32:	XQFLOAT
externdef   _Q_1E64:	XQFLOAT
externdef   _Q_1E128:	XQFLOAT
externdef   _Q_1E256:	XQFLOAT
externdef   _Q_1E512:	XQFLOAT
externdef   _Q_1E1024:	XQFLOAT
externdef   _Q_1E2048:	XQFLOAT
externdef   _Q_1E4096:	XQFLOAT
externdef   _Q_INF:	XQFLOAT
externdef   _Q_INF_M:	XQFLOAT
externdef   _Q_ZERO:	XQFLOAT
externdef   _Q_NAN:	XQFLOAT
externdef   _Q_ONE:	XQFLOAT

acosq	    proto vectorcall :XQFLOAT
acoshq	    proto vectorcall :XQFLOAT
asinq	    proto vectorcall :XQFLOAT
asinhq	    proto vectorcall :XQFLOAT
atanq	    proto vectorcall :XQFLOAT
atanhq	    proto vectorcall :XQFLOAT
atan2q	    proto vectorcall :XQFLOAT, :XQFLOAT

cbrtq	    proto vectorcall :XQFLOAT
ceilq	    proto vectorcall :XQFLOAT
copysignq   proto vectorcall :XQFLOAT, :XQFLOAT
coshq	    proto vectorcall :XQFLOAT
cosq	    proto vectorcall :XQFLOAT
erfq	    proto vectorcall :XQFLOAT
erfcq	    proto vectorcall :XQFLOAT
expq	    proto vectorcall :XQFLOAT
expm1q	    proto vectorcall :XQFLOAT
fabsq	    proto vectorcall :XQFLOAT
fdimq	    proto vectorcall :XQFLOAT
finiteq	    proto vectorcall :XQFLOAT
floorq	    proto vectorcall :XQFLOAT
fmaq	    proto vectorcall :XQFLOAT, :XQFLOAT, :XQFLOAT
fmaxq	    proto vectorcall :XQFLOAT, :XQFLOAT
fminq	    proto vectorcall :XQFLOAT, :XQFLOAT
fmodq	    proto vectorcall :XQFLOAT, :XQFLOAT
frexpq	    proto vectorcall :XQFLOAT, :ptr
hypotq	    proto vectorcall :XQFLOAT, :XQFLOAT
isinfq	    proto vectorcall :XQFLOAT
ilogbq	    proto vectorcall :XQFLOAT
isnanq	    proto vectorcall :XQFLOAT
j0q	    proto vectorcall :XQFLOAT
j1q	    proto vectorcall :XQFLOAT
jnq	    proto vectorcall :SINT, :XQFLOAT
ldexpq	    proto vectorcall :XQFLOAT, :SINT
lgammaq	    proto vectorcall :XQFLOAT
llrintq	    proto vectorcall :XQFLOAT
llroundq    proto vectorcall :XQFLOAT
logbq	    proto vectorcall :XQFLOAT
logq	    proto vectorcall :XQFLOAT
log10q	    proto vectorcall :XQFLOAT
log2q	    proto vectorcall :XQFLOAT
log1pq	    proto vectorcall :XQFLOAT
lrintq	    proto vectorcall :XQFLOAT
lroundq	    proto vectorcall :XQFLOAT
modfq	    proto vectorcall :XQFLOAT, :XQFLOAT
nanq	    proto vectorcall
nearbyintq  proto vectorcall :XQFLOAT
nextafterq  proto vectorcall :XQFLOAT, :XQFLOAT
powq	    proto vectorcall :XQFLOAT, :XQFLOAT
remainderq  proto vectorcall :XQFLOAT, :XQFLOAT
remquoq	    proto vectorcall :XQFLOAT, :XQFLOAT, :ptr
rintq	    proto vectorcall :XQFLOAT
roundq	    proto vectorcall :XQFLOAT
scalblnq    proto vectorcall :XQFLOAT, :SINT
scalbnq	    proto vectorcall :XQFLOAT, :SINT
signbitq    proto vectorcall :XQFLOAT
sincosq	    proto vectorcall :XQFLOAT, :XQFLOAT, :XQFLOAT
sinhq	    proto vectorcall :XQFLOAT
sinq	    proto vectorcall :XQFLOAT
sqrtq	    proto vectorcall :XQFLOAT
tanq	    proto vectorcall :XQFLOAT
tanhq	    proto vectorcall :XQFLOAT
tgammaq	    proto vectorcall :XQFLOAT
truncq	    proto vectorcall :XQFLOAT
y0q	    proto vectorcall :XQFLOAT
y1q	    proto vectorcall :XQFLOAT
ynq	    proto vectorcall :SINT, :XQFLOAT

quadmath_snprintf proto __cdecl :LPSTR, __size:size_t, __format:LPSTR, :vararg

mulq	    proto vectorcall :XQFLOAT, :XQFLOAT
divq	    proto vectorcall :XQFLOAT, :XQFLOAT
addq	    proto vectorcall :XQFLOAT, :XQFLOAT
subq	    proto vectorcall :XQFLOAT, :XQFLOAT
cmpq	    proto vectorcall :XQFLOAT, :XQFLOAT
normalizeq  proto vectorcall :XQFLOAT, :SINT

ifndef _INC_MATH
_DOMAIN	    equ 1 ; argument domain error
_SING	    equ 2 ; argument singularity
_OVERFLOW   equ 3 ; overflow range error
_UNDERFLOW  equ 4 ; underflow range error
_TLOSS	    equ 5 ; total loss of precision
_PLOSS	    equ 6 ; partial loss of precision
EDOM	    equ 33
ERANGE	    equ 34
endif

externdef   qerrno:SINT

ifdef _WIN64

; Using FPU -- long double precision

acosqf	    proto vectorcall :XQFLOAT
atanqf	    proto vectorcall :XQFLOAT
atan2qf	    proto vectorcall :XQFLOAT, :XQFLOAT
cbrtqf	    proto vectorcall :XQFLOAT
ceilqf	    proto vectorcall :XQFLOAT
cosqf	    proto vectorcall :XQFLOAT
expqf	    proto vectorcall :XQFLOAT
floorqf	    proto vectorcall :XQFLOAT
fmodqf	    proto vectorcall :XQFLOAT, :XQFLOAT
logqf	    proto vectorcall :XQFLOAT
log10qf	    proto vectorcall :XQFLOAT
sinqf	    proto vectorcall :XQFLOAT
sqrtqf	    proto vectorcall :XQFLOAT
tanqf	    proto vectorcall :XQFLOAT

XQFLOATTOLD macro d, x:=<xmm0>
    movq    rax,x
    shufps  x,x,01001110B
    movq    rdx,x
    shld    rcx,rdx,16
    mov	    word ptr d[8],cx
    shld    rdx,rax,16
    and	    ecx,Q_EXPMASK
    neg	    cx
    rcr	    rdx,1
    mov	    qword ptr d,rdx
    exitm<>
    endm

LDTOXQFLOAT macro d, x:=<xmm0>, tmp:=<xmm1>
    xor	    eax,eax
    mov	    rdx,qword ptr d
    mov	    cx,word ptr d[8]
    and	    ecx,Q_EXPMASK
    neg	    cx
    rcl	    rdx,1
    mov	    cx,word ptr d[8]
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    movq    tmp,rdx
    movq    x,rax
    shufpd  x,tmp,0
    exitm<>
    endm

endif

.pragma list(pop)
endif

