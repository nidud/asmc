ifndef _INC_QUADMATH
_INC_QUADMATH equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

; Parsing flags

FL_LONGDOUBLE	equ 0x0400
FL_LONGLONG	equ 0x1000
FL_CAPEXP	equ 0x10000

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
_ST_E		equ 0x1000  ; 'E' format
_ST_F		equ 0x2000  ; 'F' format
_ST_G		equ 0x4000  ; 'G' format
_ST_CVT		equ 0x8000  ; cvt routine format rules
_ST_CAPEXP	equ 0x10000

CVT_INFO	STRUC
ndigits		int_t ?
scale		int_t ?
flags		int_t ?
expchar		int_t ?
expwidth	int_t ?
sign		int_t ?
decimal_place	int_t ?
n1		int_t ?
nz1		int_t ?
n2		int_t ?
nz2		int_t ?
CVT_INFO	ENDS

; Half precision - binary16 -- REAL2 (half)

H_SIGBITS	equ 11
H_EXPBITS	equ 5
H_EXPMASK	equ (1 shl H_EXPBITS) - 1
H_EXPBIAS	equ H_EXPMASK shr 1
H_EXPMAX	equ H_EXPMASK - H_EXPBIAS

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

if defined(_WIN64) and not defined(_XM_NO_INTRINSICS_)
QFCALLCONV	equ <vectorcall>
QCALLCONVR	equ <vectorcall>
XQFLOAT		typedef REAL16
XQREAL2		typedef REAL2
XQREAL4		typedef REAL4
XQREAL8		typedef REAL8
XQREAL10	typedef REAL10
PQFLOAT		typedef ptr REAL16
else
QFCALLCONV	equ <__cdecl>
QCALLCONVR	equ <__cdecl x:ptr,>
XQFLOAT		typedef ptr
XQREAL2		typedef ptr
XQREAL4		typedef ptr
XQREAL8		typedef ptr
XQREAL10	typedef ptr
PQFLOAT		typedef ptr
endif

addq		proto QFCALLCONV :XQFLOAT, :XQFLOAT
subq		proto QFCALLCONV :XQFLOAT, :XQFLOAT
divq		proto QFCALLCONV :XQFLOAT, :XQFLOAT
mulq		proto QFCALLCONV :XQFLOAT, :XQFLOAT
normq		proto QFCALLCONV :XQFLOAT, :int_t
cvtq_h		proto QCALLCONVR :XQFLOAT
cvtq_ss		proto QCALLCONVR :XQFLOAT
cvtq_sd		proto QCALLCONVR :XQFLOAT
cvtq_ld		proto QCALLCONVR :XQFLOAT
cvtq_i32	proto QFCALLCONV :XQFLOAT
cvtq_i64	proto QFCALLCONV :XQFLOAT
cvtq_a		proto QFCALLCONV :XQFLOAT, :ptr, :string_t, :uint_t
cvth_q		proto QCALLCONVR :XQREAL2
cvtss_q		proto QCALLCONVR :XQREAL4
cvtsd_q		proto QCALLCONVR :XQREAL8
cvtld_q		proto QCALLCONVR :XQREAL10
cvti32_q	proto QCALLCONVR :long_t
cvti64_q	proto QCALLCONVR :int64_t
cvta_q		proto QCALLCONVR :string_t, :ptr string_t
cmpq		proto QFCALLCONV :XQFLOAT, :XQFLOAT
cfltcvt		proto QFCALLCONV :XQREAL8, :string_t, :int_t, :int_t, :int_t
cldcvt		proto QFCALLCONV :XQREAL10, :string_t, :int_t, :int_t, :int_t
cqfcvt		proto QFCALLCONV :XQFLOAT, :string_t, :int_t, :int_t, :int_t

ifndef _WIN64
_udiv256	proto __cdecl :ptr, :ptr, :ptr
_mul256		proto __cdecl :ptr, :ptr, :ptr
endif

quadisinf	proto __cdecl :ptr
quadisnan	proto __cdecl :ptr
strtoflt128	proto __cdecl :string_t, :ptr string_t


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

FLTQ macro value
  local string
    string textequ <FLT8@>
    forc q,<value>
	ifidn <q>,<->
	    string CatStr string, <M>
	elseifidn <q>,<+>
	    string CatStr string, <P>
	elseifidn <q>,< >
	    string CatStr string, <_>
	elseifidn <q>,<*>
	    string CatStr string, <x>
	elseifidn <q>,</>
	    string CatStr string, <d>
	elseifidn <q>,<.>
	    string CatStr string, <_>
	elseifidn <q>,<(>
	    exitm
	else
	    string CatStr string, <q>
	endif
	endm
%   ifndef string
	.data
	align 16
	string oword value
	.code
    endif
    exitm<string>
    endm

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
    shl	    rdx,1
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

