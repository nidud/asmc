.pragma list(push, 0)

ifndef _INC_QUADMATH
define _INC_QUADMATH

include fltintrn.inc
include errno.inc
include limits.inc

ifdef _WIN64

addq		proto __cdecl :real16, :real16
subq		proto __cdecl :real16, :real16
divq		proto __cdecl :real16, :real16
mulq		proto __cdecl :real16, :real16
cmpq		proto __cdecl :real16, :real16
cvtqh		proto __cdecl :real16
cvtqss		proto __cdecl :real16
cvtqsd		proto __cdecl :real16
cvtqld		proto __cdecl :real16
cvtqsi		proto __cdecl :real16
cvttqsi		proto __cdecl :real16
cvthq		proto __cdecl :real2
cvtssq		proto __cdecl :real4
cvtsdq		proto __cdecl :real8
cvtldq		proto __cdecl :real10
cvtsiq		proto __cdecl :ptr int128_t
cvtaq		proto __cdecl :string_t, :ptr string_t
qtofpu		proto __cdecl :real16
fputoq		proto __cdecl

acosq		proto __cdecl :real16
acoshq		proto __cdecl :real16
asinq		proto __cdecl :real16
asinhq		proto __cdecl :real16
atanq		proto __cdecl :real16
atanhq		proto __cdecl :real16
atan2q		proto __cdecl :real16, :real16

cbrtq		proto __cdecl :real16
ceilq		proto __cdecl :real16
copysignq	proto __cdecl :real16, :real16
coshq		proto __cdecl :real16
cosq		proto __cdecl :real16
erfq		proto __cdecl :real16
erfcq		proto __cdecl :real16
expq		proto __cdecl :real16
expm1q		proto __cdecl :real16
fabsq		proto __cdecl :real16
fdimq		proto __cdecl :real16
finiteq		proto __cdecl :real16
floorq		proto __cdecl :real16
fmaq		proto __cdecl :real16, :real16, :real16
fmaxq		proto __cdecl :real16, :real16
fminq		proto __cdecl :real16, :real16
fmodq		proto __cdecl :real16, :real16
frexpq		proto __cdecl :real16, :ptr
hypotq		proto __cdecl :real16, :real16
isinfq		proto __cdecl :real16
ilogbq		proto __cdecl :real16
isnanq		proto __cdecl :real16
isinf_nsq	proto __cdecl :real16
j0q		proto __cdecl :real16
j1q		proto __cdecl :real16
jnq		proto __cdecl :int_t, :real16
ldexpq		proto __cdecl :real16, :int_t
lgammaq		proto __cdecl :real16
llrintq		proto __cdecl :real16
llroundq	proto __cdecl :real16
logbq		proto __cdecl :real16
logq		proto __cdecl :real16
log10q		proto __cdecl :real16
log2q		proto __cdecl :real16
log1pq		proto __cdecl :real16
lrintq		proto __cdecl :real16
lroundq		proto __cdecl :real16
modfq		proto __cdecl :real16, :real16
nanq		proto __cdecl
nearbyintq	proto __cdecl :real16
nextafterq	proto __cdecl :real16, :real16
powq		proto __cdecl :real16, :real16
remainderq	proto __cdecl :real16, :real16
remquoq		proto __cdecl :real16, :real16, :ptr
rintq		proto __cdecl :real16
roundq		proto __cdecl :real16
scalblnq	proto __cdecl :real16, :int_t
scalbnq		proto __cdecl :real16, :int_t
signbitq	proto __cdecl :real16
sincosq		proto __cdecl :real16, :real16, :real16
sinhq		proto __cdecl :real16
sinq		proto __cdecl :real16
sqrtq		proto __cdecl :real16
tanq		proto __cdecl :real16
tanhq		proto __cdecl :real16
tgammaq		proto __cdecl :real16
truncq		proto __cdecl :real16
y0q		proto __cdecl :real16
y1q		proto __cdecl :real16
ynq		proto __cdecl :int_t, :real16

endif ; _WIN64

endif

.pragma list(pop)
