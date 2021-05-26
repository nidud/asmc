.pragma list(push, 0)

ifndef _INC_QUADMATH
_INC_QUADMATH equ <>

include fltintrn.inc

; Quadruple precision constants

M_E		equ 2.71828182845904523536028747135266249775724709369996
M_LOG2E		equ 1.44269504088896340735992468100189213742664595415299
M_LOG10E	equ 0.43429448190325182765112891891660508229439700580367
M_LN2		equ 0.69314718055994530941723212145817656807550013436026
M_LN10		equ 2.30258509299404568401799145468436420760110148862877
M_PI		equ 3.14159265358979323846264338327950288419716939937511
M_PI_2		equ 1.57079632679489661923132169163975144209858469968755
M_PI_4		equ 0.78539816339744830961566084581987572104929234984378
M_1_PI		equ 0.31830988618379067153776752674502872406891929148091
M_2_PI		equ 0.63661977236758134307553505349005744813783858296183
M_2_SQRTPI	equ 1.12837916709551257389615890312154517168810125865800
M_SQRT2		equ 1.41421356237309504880168872420969807856967187537695
M_SQRT1_2	equ 0.70710678118654752440084436210484903928483593768847
M_SQRT3		equ 1.73205080756887729352744634150587236694280525381038
M_TWOPI		equ 6.28318530717958647692528676655900576839433879875021
M_3PI_4		equ 2.35619449019234492884698253745962716314787704953133
M_SQRTPI	equ 1.77245385090551602729816748334114518279754945612239
M_LOGE		equ M_LOG10E
M_IVLN10	equ M_LOG10E
M_LOG2_E	equ M_LN2
M_INVLN2	equ M_LOG2E
M_LOG2		equ 0.30102999566398119521373889472449302676818988146211
M_1_SQRTPI	equ 0.56418958354775628694807945156077258584405062932900
M_LN2_SQUARED	equ 0.48045301391820142466710252632666497173055295159455
M_LN2_CUBED	equ 0.33302465198892947971885358261173054415612648534861
M_LI2		equ 1.045163780117492784844588889194613136522615578
M_C2		equ 0.660161815846869573927812110014555778432623360
M_C3		equ 0.635166354604271207206696591272522417342065687
M_C4		equ 0.307494878758327093123354486071076853022178520
M_HL2		equ 1.320323631693739147855624220029111556865246721
M_HL3		equ 2.858248595719220432430134660726350878039295593
M_HL4		equ 4.151180863237415757165285561959537515799410019
M_ACC2		equ 2.640647263387478295711248440058223113730493441
M_ACC3		equ 4.287372893578830648645201991089526317058943389
M_ACC4		equ 5.534907817649887676220380749279383354399213359
INFINITY	equ 1.0e999999999
NAN		equ (0.0 / 0.0)

; */+-
; Return pointer to A (result)

__mulq		proto __cdecl A:ptr, B:ptr
__divq		proto __cdecl A:ptr, B:ptr
__addq		proto __cdecl A:ptr, B:ptr
__subq		proto __cdecl A:ptr, B:ptr
__cmpq		proto __cdecl A:ptr, B:ptr
__sqrtq		proto __cdecl A:ptr

; Convert HALF, float, double, long double, int, __int64, string

__cvtq_h	proto __cdecl dst:ptr, Q:ptr
__cvtq_ss	proto __cdecl dst:ptr, Q:ptr
__cvtq_sd	proto __cdecl dst:ptr, Q:ptr
__cvtq_ld	proto __cdecl dst:ptr, Q:ptr
__cvtq_i32	proto __cdecl :ptr
__cvtq_i64	proto __cdecl :ptr
__cvth_q	proto __cdecl :ptr, :ptr
__cvtss_q	proto __cdecl :ptr, :ptr
__cvtsd_q	proto __cdecl :ptr, :ptr
__cvtld_q	proto __cdecl :ptr, :ptr
__cvti32_q	proto __cdecl :ptr, :long_t
__cvti64_q	proto __cdecl :ptr, :int64_t
__cvta_q	proto __cdecl :ptr, :string_t, :ptr string_t


__addo		proto __cdecl :ptr, :ptr
__subo		proto __cdecl :ptr, :ptr
__mulo		proto __cdecl :ptr, :ptr, :ptr
__divo		proto __cdecl :ptr, :ptr, :ptr
__shlo		proto __cdecl :ptr, :int_t, :int_t
__shro		proto __cdecl :ptr, :int_t, :int_t
__saro		proto __cdecl :ptr, :int_t, :int_t

ifdef _WIN64
ifdef _LINUX
__vectorcall	equ <syscall>
else
__vectorcall	equ <vectorcall>
endif

addq		proto __vectorcall :real16, :real16
subq		proto __vectorcall :real16, :real16
divq		proto __vectorcall :real16, :real16
mulq		proto __vectorcall :real16, :real16
cmpq		proto __vectorcall :real16, :real16
cvtq_h		proto __vectorcall :real16
cvtq_ss		proto __vectorcall :real16
cvtq_sd		proto __vectorcall :real16
cvtq_ld		proto __vectorcall :real16
cvtq_i32	proto __vectorcall :real16
cvtq_i64	proto __vectorcall :real16
cvth_q		proto __vectorcall :real2
cvtss_q		proto __vectorcall :real4
cvtsd_q		proto __vectorcall :real8
cvtld_q		proto __vectorcall :real10
cvti32_q	proto __vectorcall :long_t
cvti64_q	proto __vectorcall :int64_t
cvta_q		proto __vectorcall :string_t, :ptr string_t
qtofpu		proto __vectorcall :real16
fputoq		proto __vectorcall

fltscale	proto __vectorcall :real16, :int_t
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
isinf_nsq	proto __vectorcall :real16
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

fldq macro this:=<d>, xmm:=<xmm0>

  .new d:tbyte

    movq    rax,xmm
    movhlps xmm,xmm
    movq    rdx,xmm
    shld    rcx,rdx,16
    mov	    word ptr this[8],cx
    shld    rdx,rax,16
    and	    ecx,Q_EXPMASK
    neg	    cx
    rcr	    rdx,1
    mov	    qword ptr this,rdx
    fld	    this
    exitm   <>
    endm

fstq macro
    fstp    d
    xor	    eax,eax
    mov	    rdx,qword ptr d
    shl	    rdx,1
    mov	    cx,word ptr d[8]
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1
    exitm   <>
    endm

endif ; _WIN64

endif

.pragma list(pop)

