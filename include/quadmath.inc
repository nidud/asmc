.pragma list(push, 0)

ifndef _INC_QUADMATH
_INC_QUADMATH equ <>

include fltintrn.inc

; Parsing flags

FL_LONGDOUBLE	equ 0x0400
FL_LONGLONG	equ 0x1000
FL_CAPEXP	equ 0x10000

; Quadruple precision constants

externdef	_Q_E:		real16 ; e
externdef	_Q_LOG2E:	real16 ; log2(e)
externdef	_Q_LOG10E:	real16 ; log10(e)
externdef	_Q_LN2:		real16 ; ln(2)
externdef	_Q_LN10:	real16 ; ln(10)
externdef	_Q_PI:		real16 ; pi
externdef	_Q_PI_2:	real16 ; pi/2
externdef	_Q_PI_4:	real16 ; pi/4
externdef	_Q_1_PI:	real16 ; 1/pi
externdef	_Q_2_PI:	real16 ; 2/pi
externdef	_Q_2_SQRTPI:	real16 ; 2/sqrt(pi)
externdef	_Q_SQRT2:	real16 ; sqrt(2)
externdef	_Q_SQRT1_2:	real16 ; 1/sqrt(2)
externdef	_Q_1E1:		real16 ; table..
externdef	_Q_1E2:		real16
externdef	_Q_1E4:		real16
externdef	_Q_1E8:		real16
externdef	_Q_1E16:	real16
externdef	_Q_1E32:	real16
externdef	_Q_1E64:	real16
externdef	_Q_1E128:	real16
externdef	_Q_1E256:	real16
externdef	_Q_1E512:	real16
externdef	_Q_1E1024:	real16
externdef	_Q_1E2048:	real16
externdef	_Q_1E4096:	real16
externdef	_Q_INF:		real16
externdef	_Q_INF_M:	real16
externdef	_Q_ZERO:	real16
externdef	_Q_NAN:		real16
externdef	_Q_ONE:		real16

; */+-
; Return pointer to A (result)

__mulq		proto __cdecl A:ptr, B:ptr
__divq		proto __cdecl A:ptr, B:ptr
__addq		proto __cdecl A:ptr, B:ptr
__subq		proto __cdecl A:ptr, B:ptr
__cmpq		proto __cdecl A:ptr, B:ptr
__fltscale	proto __cdecl Q:ptr, :int_t

; Convert HALF, float, double, long double, int, __int64, string

__cvtq_h	proto __cdecl dst:ptr, Q:ptr
__cvtq_ss	proto __cdecl dst:ptr, Q:ptr
__cvtq_sd	proto __cdecl dst:ptr, Q:ptr
__cvtq_ld	proto __cdecl dst:ptr, Q:ptr
__cvtq_i32	proto __cdecl :ptr
__cvtq_i64	proto __cdecl :ptr
__cvtq_a	proto __cdecl :ptr, :ptr, :string_t, :uint_t
__cvth_q	proto __cdecl :ptr, :ptr
__cvtss_q	proto __cdecl :ptr, :ptr
__cvtsd_q	proto __cdecl :ptr, :ptr
__cvtld_q	proto __cdecl :ptr, :ptr
__cvti32_q	proto __cdecl :ptr, :long_t
__cvti64_q	proto __cdecl :ptr, :int64_t
__cvta_q	proto __cdecl :ptr, :string_t, :ptr string_t

__vectorcall	equ <vectorcall>

addq		proto __vectorcall :real16, :real16
subq		proto __vectorcall :real16, :real16
divq		proto __vectorcall :real16, :real16
mulq		proto __vectorcall :real16, :real16
fltscale	proto __vectorcall :real16, :int_t
cmpq		proto __vectorcall :real16, :real16
cvtq_h		proto __vectorcall :real16
cvtq_ss		proto __vectorcall :real16
cvtq_sd		proto __vectorcall :real16
cvtq_ld		proto __vectorcall :real16
cvtq_i32	proto __vectorcall :real16
cvtq_i64	proto __vectorcall :real16
cvtq_a		proto __vectorcall :real16, :ptr, :string_t, :uint_t
cvth_q		proto __vectorcall :real2
cvtss_q		proto __vectorcall :real4
cvtsd_q		proto __vectorcall :real8
cvtld_q		proto __vectorcall :real10
cvti32_q	proto __vectorcall :long_t
cvti64_q	proto __vectorcall :int64_t
cvta_q		proto __vectorcall :string_t, :ptr string_t

cfltcvt		proto __vectorcall :real8, :string_t, :int_t, :int_t, :int_t
cldcvt		proto __vectorcall :real10, :string_t, :int_t, :int_t, :int_t
cqfcvt		proto __vectorcall :real16, :string_t, :int_t, :int_t, :int_t
strtoflt128	proto __vectorcall :string_t, :ptr string_t

acosq		proto __vectorcall :real16
acoshq		proto __vectorcall :real16
asinq		proto __vectorcall :real16
asinhq		proto __vectorcall :real16
atanq		proto __vectorcall :real16
atanhq		proto __vectorcall :real16
atan2q		proto __vectorcall :real16, :real16

cbrtq		proto __vectorcall :real16
ceilq		proto __vectorcall :real16
copysignq	proto __vectorcall :real16, :real16
coshq		proto __vectorcall :real16
cosq		proto __vectorcall :real16
erfq		proto __vectorcall :real16
erfcq		proto __vectorcall :real16
expq		proto __vectorcall :real16
expm1q		proto __vectorcall :real16
fabsq		proto __vectorcall :real16
fdimq		proto __vectorcall :real16
finiteq		proto __vectorcall :real16
floorq		proto __vectorcall :real16
fmaq		proto __vectorcall :real16, :real16, :real16
fmaxq		proto __vectorcall :real16, :real16
fminq		proto __vectorcall :real16, :real16
fmodq		proto __vectorcall :real16, :real16
frexpq		proto __vectorcall :real16, :ptr
hypotq		proto __vectorcall :real16, :real16
isinfq		proto __vectorcall :real16
ilogbq		proto __vectorcall :real16
isnanq		proto __vectorcall :real16
j0q		proto __vectorcall :real16
j1q		proto __vectorcall :real16
jnq		proto __vectorcall :SINT, :real16
ldexpq		proto __vectorcall :real16, :SINT
lgammaq		proto __vectorcall :real16
llrintq		proto __vectorcall :real16
llroundq	proto __vectorcall :real16
logbq		proto __vectorcall :real16
logq		proto __vectorcall :real16
log10q		proto __vectorcall :real16
log2q		proto __vectorcall :real16
log1pq		proto __vectorcall :real16
lrintq		proto __vectorcall :real16
lroundq		proto __vectorcall :real16
modfq		proto __vectorcall :real16, :real16
nanq		proto __vectorcall
nearbyintq	proto __vectorcall :real16
nextafterq	proto __vectorcall :real16, :real16
powq		proto __vectorcall :real16, :real16
remainderq	proto __vectorcall :real16, :real16
remquoq		proto __vectorcall :real16, :real16, :ptr
rintq		proto __vectorcall :real16
roundq		proto __vectorcall :real16
scalblnq	proto __vectorcall :real16, :SINT
scalbnq		proto __vectorcall :real16, :SINT
signbitq	proto __vectorcall :real16
sincosq		proto __vectorcall :real16, :real16, :real16
sinhq		proto __vectorcall :real16
sinq		proto __vectorcall :real16
sqrtq		proto __vectorcall :real16
tanq		proto __vectorcall :real16
tanhq		proto __vectorcall :real16
tgammaq		proto __vectorcall :real16
truncq		proto __vectorcall :real16
y0q		proto __vectorcall :real16
y1q		proto __vectorcall :real16
ynq		proto __vectorcall :SINT, :real16

quadmath_snprintf proto __cdecl :string_t, :size_t, :string_t, :vararg

ifndef _INC_MATH
_DOMAIN		equ 1 ; argument domain error
_SING		equ 2 ; argument singularity
_OVERFLOW	equ 3 ; overflow range error
_UNDERFLOW	equ 4 ; underflow range error
_TLOSS		equ 5 ; total loss of precision
_PLOSS		equ 6 ; partial loss of precision
EDOM		equ 33
ERANGE		equ 34
endif

ifdef _WIN64

; Using FPU -- long double precision

acosqf		proto __vectorcall :real16
atanqf		proto __vectorcall :real16
atan2qf		proto __vectorcall :real16, :real16
cbrtqf		proto __vectorcall :real16
ceilqf		proto __vectorcall :real16
cosqf		proto __vectorcall :real16
expqf		proto __vectorcall :real16
floorqf		proto __vectorcall :real16
fmodqf		proto __vectorcall :real16, :real16
logqf		proto __vectorcall :real16
log10qf		proto __vectorcall :real16
sinqf		proto __vectorcall :real16
sqrtqf		proto __vectorcall :real16
tanqf		proto __vectorcall :real16

FLTQ macro value
  local string
    string textequ <FLTQ@>
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
	string label real16
	oword value
	.code
    endif
    exitm<string>
    endm

fldq macro this:=<rsp>, xmm:=<xmm0>
    movaps  [this],xmm
    mov	    rax,[this]
    mov	    rdx,[this+8]
    shld    r8,rdx,16
    mov	    [this+8],r8w
    shld    rdx,rax,16
    and	    r8d,Q_EXPMASK
    neg	    r8w
    rcr	    rdx,1
    mov	    [this],rdx
    fld	    real10 ptr [this]
    retm    <this>
    endm

fstq macro this:=<rsp>, xmm:=<xmm0>
    fstp    real10 ptr [this]
    xor	    eax,eax
    mov	    rdx,[this]
    shl	    rdx,1
    mov	    r8w,[this+8]
    shrd    rax,rdx,16
    shrd    rdx,r8,16
    mov	    [this],rax
    mov	    [this+8],rdx
    movaps  xmm,[this]
    retm    <xmm>
    endm

endif
endif

.pragma list(pop)

