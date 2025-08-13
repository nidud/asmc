.pragma list(push, 0)

include libc.inc

ifndef float
float  typedef real4
endif
ifndef double
double typedef real8
endif

FLT_DIG		equ 6		    ;; # of decimal digits of precision
FLT_EPSILON	equ 1.192092896e-07 ;; smallest such that 1.0+FLT_EPSILON != 1.0
FLT_GUARD	equ 0
FLT_MANT_DIG	equ 24		    ;; # of bits in mantissa
FLT_MAX		equ 3.402823466e+38 ;; max value
FLT_MAX_10_EXP	equ 38		    ;; max decimal exponent
FLT_MAX_EXP	equ 128		    ;; max binary exponent
FLT_MIN		equ 1.175494351e-38 ;; min positive value
FLT_MIN_10_EXP	equ (-37)	    ;; min decimal exponent
FLT_MIN_EXP	equ (-125)	    ;; min binary exponent
FLT_NORMALIZE	equ 0
FLT_RADIX	equ 2		    ;; exponent radix
FLT_ROUNDS	equ 1		    ;; addition rounding: near
FLT_EXPBITS	equ 8
FLT_EXPMASK	equ (1 shl FLT_EXPBITS) - 1

DBL_DIG		equ 15
DBL_EPSILON	equ 2.2204460492503131e-016
DBL_MANT_DIG	equ 53
DBL_MAX		equ 1.7976931348623158e+308
DBL_MAX_10_EXP	equ 308
DBL_MAX_EXP	equ 1024
DBL_MIN		equ 2.2250738585072014e-308
DBL_MIN_10_EXP	equ (-307)
DBL_MIN_EXP	equ (-1021)
_DBL_RADIX	equ 2
_DBL_ROUNDS	equ 1
DBL_EXPBITS	equ 11
DBL_EXPMASK	equ (1 shl DBL_EXPBITS) - 1

LDBL_DIG	equ 18
LDBL_EPSILON	equ 1.08420217248550443412e-019
LDBL_MANT_DIG	equ 64
LDBL_MAX	equ 1.189731495357231765e+4932
LDBL_MAX_10_EXP equ 4932
LDBL_MAX_EXP	equ 16384
LDBL_MIN	equ 3.3621031431120935063e-4932
LDBL_MIN_10_EXP equ (-4931)
LDBL_MIN_EXP	equ (-16381)
_LDBL_RADIX	equ 2
_LDBL_ROUNDS	equ 1
LDBL_EXPBITS	equ 15
LDBL_EXPMASK	equ (1 shl LDBL_EXPBITS) - 1

; Control word masks for unMask

_MCW_EM		equ 0x0008001F ; Error masks
_MCW_IC		equ 0x00040000 ; Infinity
_MCW_RC		equ 0x00000300 ; Rounding
_MCW_PC		equ 0x00030000 ; Precision

; Control word values for unNew (use with related unMask above)
_EM_INVALID	equ 0x00000010
_EM_DENORMAL	equ 0x00080000
_EM_ZERODIVIDE	equ 0x00000008
_EM_OVERFLOW	equ 0x00000004
_EM_UNDERFLOW	equ 0x00000002
_EM_INEXACT	equ 0x00000001
_IC_AFFINE	equ 0x00040000
_IC_PROJECTIVE	equ 0x00000000
_RC_CHOP	equ 0x00000300
_RC_UP		equ 0x00000200
_RC_DOWN	equ 0x00000100
_RC_NEAR	equ 0x00000000
_PC_24		equ 0x00020000
_PC_53		equ 0x00010000
_PC_64		equ 0x00000000

_FPCLASS_SNAN	equ 0x0001 ; Signaling "Not a Number"
_FPCLASS_QNAN	equ 0x0002 ; Quiet "Not a Number"
_FPCLASS_NINF	equ 0x0004 ; Negative Infinity
_FPCLASS_NN	equ 0x0008 ; Negative Normal
_FPCLASS_ND	equ 0x0010 ; Negative Denormal
_FPCLASS_NZ	equ 0x0020 ; Negative Zero
_FPCLASS_PZ	equ 0x0040 ; Positive Zero
_FPCLASS_PD	equ 0x0080 ; Positive Denormal
_FPCLASS_PN	equ 0x0100 ; Positive Normal
_FPCLASS_PINF	equ 0x0200 ; Positive Infinity

; _statusfp bit flags

_SW_INEXACT		equ 0x00000001 ; inexact (precision)
_SW_UNDERFLOW		equ 0x00000002 ; underflow
_SW_OVERFLOW		equ 0x00000004 ; overflow
_SW_ZERODIVIDE		equ 0x00000008 ; zero divide
_SW_INVALID		equ 0x00000010 ; invalid
_SW_DENORMAL		equ 0x00080000 ; denormal status bit

_SW_UNEMULATED		equ 0x00000040 ; unemulated instruction
_SW_SQRTNEG		equ 0x00000080 ; square root of a neg number
_SW_STACKOVERFLOW	equ 0x00000200 ; FP stack overflow
_SW_STACKUNDERFLOW	equ 0x00000400 ; FP stack underflow

;  Floating point error signals and return codes

_FPE_INVALID		equ 0x81
_FPE_DENORMAL		equ 0x82
_FPE_ZERODIVIDE		equ 0x83
_FPE_OVERFLOW		equ 0x84
_FPE_UNDERFLOW		equ 0x85
_FPE_INEXACT		equ 0x86
_FPE_UNEMULATED		equ 0x87
_FPE_SQRTNEG		equ 0x88
_FPE_STACKOVERFLOW	equ 0x8a
_FPE_STACKUNDERFLOW	equ 0x8b
_FPE_EXPLICITGEN	equ 0x8c	; raise( SIGFPE )
_FPE_MULTIPLE_TRAPS	equ 0x8d	; on x86 with arch:SSE2 OS returns these exceptions
_FPE_MULTIPLE_FAULTS	equ 0x8e


;; Set the FPU control word as cw = (cw & ~unMask) | (unNew & unMask),
;; i.e. change the bits in unMask to have the values they have in unNew,
;; leaving other bits unchanged.

_controlfp	proto __cdecl :uint_t, :uint_t
_control87	proto __cdecl :uint_t, :uint_t

_clearfp	proto __cdecl ; Clear the FPU status word
_statusfp	proto __cdecl ; Report the FPU status word
_clear87	equ <_clearfp>
_status87	equ <_statusfp>

;;
;; MSVCRT.dll _fpreset initializes the control register to 0x27f,
;; the status register to zero and the tag word to 0FFFFh.
;; This differs from asm instruction finit/fninit which set control
;; word to 0x37f (64 bit mantissa precison rather than 53 bit).
;; By default, the mingw version of _fpreset sets fp control as
;; per fninit. To use the MSVCRT.dll _fpreset, include CRT_fp8.o when
;; building your application.
;;
_fpreset	proto __cdecl

;;
;; IEEE recommended functions.	MS puts them in float.h
;; but they really belong in math.h.
;;

ifndef _SIGN_DEFINED
define _SIGN_DEFINED
_copysign proto __cdecl _Number:double, _Sign:double
_chgsign proto __cdecl _X:double
endif

_logb		proto __cdecl :double
_scalb		proto __cdecl :double, :int_t

_finite		proto __cdecl :double
_fpclass	proto __cdecl :double
_isnan		proto __cdecl :double

.pragma list(pop)
