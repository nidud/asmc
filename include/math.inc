.pragma list(push, 0)
ifndef _INC_MATH
_INC_MATH equ <>
ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc, msvcrt)

ifndef double
double typedef REAL8
endif

ifndef __assembler ; Protect from assembler

ifndef _EXCEPTION_DEFINED
_exception      struc
_type           SINT ?      ; exception type - see below
_name           LPSTR ?     ; name of function where error occured
arg1            double ?    ; first argument to function
arg2            double ?    ; second argument (if any) to function
retval          double ?    ; value to be returned by function
_exception      ends
_EXCEPTION_DEFINED equ <>
endif

ifndef _COMPLEX_DEFINED
_complex        struc
x               double ? ; real and imaginary parts
y               double ?
_complex        ends
ifndef __STDC__
complex         equ <_complex>
endif
_COMPLEX_DEFINED equ <>
endif
endif  ; __assembler

_DOMAIN         equ 1 ; argument domain error
_SING           equ 2 ; argument singularity
_OVERFLOW       equ 3 ; overflow range error
_UNDERFLOW      equ 4 ; underflow range error
_TLOSS          equ 5 ; total loss of precision
_PLOSS          equ 6 ; partial loss of precision

EDOM            equ 33
ERANGE          equ 34

ifndef __assembler ; Protect from assembler
ifndef _M_CEE_PURE
externdef       _HUGE:double
else
;const double _HUGE = System::Double::PositiveInfinity;
endif ; !defined(_M_CEE_PURE)
endif ; __assembler

HUGE_VAL        equ <_HUGE>

ifndef __assembler  ; Protect from assembler
ifndef _CRT_ABS_DEFINED
_CRT_ABS_DEFINED equ <>
abs     proto __cdecl _X:SINT
labs    proto __cdecl _X:sdword
endif

acos    proto __cdecl _X:double
asin    proto __cdecl _X:double
atan    proto __cdecl _X:double
atan2   proto __cdecl _Y:double, _X:double
ifndef _SIGN_DEFINED
copysign proto __cdecl _Number:double, _Sign:double
_chgsign proto __cdecl _X:double
_SIGN_DEFINED equ <>
endif
cos     proto __cdecl _X:double
cosh    proto __cdecl _X:double
exp     proto __cdecl _X:double
exp2    proto __cdecl _X:double
_fabs   proto __cdecl _X:double
fmod    proto __cdecl _X:double, _Y:double
log     proto __cdecl _X:double
log10   proto __cdecl _X:double
pow     proto __cdecl _X:double, _Y:double
sin     proto __cdecl _X:double
sinh    proto __cdecl _X:double
tan     proto __cdecl _X:double
tanh    proto __cdecl _X:double
sqrt    proto __cdecl _X:double

ifndef _CRT_ATOF_DEFINED
_CRT_ATOF_DEFINED equ <>
atof    proto __cdecl _String:LPSTR
_atof_l proto __cdecl _String:LPSTR, _Locale:SINT;_locale_t
endif

_cabs   proto __cdecl _Complex_value:_complex
ceil    proto __cdecl _X:double
floor   proto __cdecl _X:double
frexp   proto __cdecl _X:double, _Y:ptr SINT
_hypot  proto __cdecl _X:double, _Y:double
_j0     proto __cdecl _X:double
_j1     proto __cdecl _X:double
_jn     proto __cdecl _X:SINT, _Y:double
ldexp   proto __cdecl _X:double, _Y:SINT
ifndef _CRT_MATHERR_DEFINED
_CRT_MATHERR_DEFINED equ <>
_matherr proto __cdecl _Except:ptr _exception
endif
modf    proto __cdecl _X:double, _Y:ptr double

_y0     proto __cdecl _X:double
_y1     proto __cdecl _X:double
_yn     proto __cdecl _X:SINT, _Y:double

round   proto __cdecl _X:double

ifndef float
float  typedef real4
endif

ifdef _M_IX86

_set_SSE2_enable proto __cdecl _Flag:SINT
_hypotf proto __cdecl _X:float, _Y:float

endif

ifdef _M_IA64

acosf   proto __cdecl _X:float
asinf   proto __cdecl _X:float
atanf   proto __cdecl _X:float
atan2f  proto __cdecl _X:float, _Y:float
cosf    proto __cdecl _X:float
sinf    proto __cdecl _X:float
tanf    proto __cdecl _X:float

coshf   proto __cdecl _X:float
sinhf   proto __cdecl _X:float
tanhf   proto __cdecl _X:float

expf    proto __cdecl _X:float
logf    proto __cdecl _X:float
log10f  proto __cdecl _X:float
modff   proto __cdecl _X:float, _Y:ptr float

powf    proto __cdecl _Base:float, _Exp:float
sqrtf   proto __cdecl _X:float

ceilf   proto __cdecl _X:float
fabsf   proto __cdecl _X:float
floorf  proto __cdecl _X:float
fmodf   proto __cdecl _X:float, _Y:float

_hypotf proto __cdecl _X:float, _Y:float
ldexpf  proto __cdecl _X:float, _Y:SINT

endif

roundf  proto __cdecl _X:float

ifdef _M_AMD64

acosf   proto __cdecl _X:float
asinf   proto __cdecl _X:float
atanf   proto __cdecl _X:float
atan2f  proto __cdecl _X:float, _Y:float
cosf    proto __cdecl _X:float
sinf    proto __cdecl _X:float
tanf    proto __cdecl _X:float

coshf   proto __cdecl _X:float
sinhf   proto __cdecl _X:float
tanhf   proto __cdecl _X:float

expf    proto __cdecl _X:float
logf    proto __cdecl _X:float
log10f  proto __cdecl _X:float
modff   proto __cdecl _X:float, _Y:ptr float

powf    proto __cdecl _X:float, _Y:float
sqrtf   proto __cdecl _X:float

ceilf   proto __cdecl _X:float
floorf  proto __cdecl _X:float
fmodf   proto __cdecl _X:float, _Y:float

_hypotf proto __cdecl _X:float, _Y:float

copysignf   proto __cdecl _Number:float, _Sign:float
_chgsignf   proto __cdecl _X:float
_logbf      proto __cdecl _X:float
_nextafterf proto __cdecl _X:float, _Y:float
_finitef    proto __cdecl _X:float
_isnanf     proto __cdecl _X:float
_fpclassf   proto __cdecl _X:float

endif
endif
endif

ifdef _USE_MATH_DEFINES
ifndef _MATH_DEFINES_DEFINED
_MATH_DEFINES_DEFINED equ <>
M_E             equ 2.71828182845904523536
M_LOG2E         equ 1.44269504088896340736
M_LOG10E        equ 0.434294481903251827651
M_LN2           equ 0.693147180559945309417
M_LN10          equ 2.30258509299404568402
M_PI            equ 3.14159265358979323846
M_PI_2          equ 1.57079632679489661923
M_PI_4          equ 0.785398163397448309616
M_1_PI          equ 0.318309886183790671538
M_2_PI          equ 0.636619772367581343076
M_2_SQRTPI      equ 1.12837916709551257390
M_SQRT2         equ 1.41421356237309504880
M_SQRT1_2       equ 0.707106781186547524401
INFINITY        equ 1.0e999999999
NAN             equ 0.0/0.0
endif
endif
.pragma list(pop)
