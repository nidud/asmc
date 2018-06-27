.pragma list(push, 0)

include libc.inc

ifndef double
double typedef REAL8
endif

; Single precision - binary32 -- REAL4 (float) 1:8:23

F_SIGBITS	equ 24
F_EXPBITS	equ 8
F_EXPMASK	equ (1 shl F_EXPBITS) - 1
F_EXPBIAS	equ F_EXPMASK shr 1
F_EXPMAX	equ F_EXPMASK - F_EXPBIAS

; Double precision - binary64 -- REAL8 (double) 1:11:53

D_SIGBITS	equ 53
D_EXPBITS	equ 11
D_EXPMASK	equ (1 shl D_EXPBITS) - 1
D_EXPBIAS	equ D_EXPMASK shr 1
D_EXPMAX	equ D_EXPMASK - D_EXPBIAS

; Long Double precision - binary80 -- REAL10 (long double) 1:15:64

LD_SIGBITS	equ 64
LD_EXPBITS	equ 15
LD_EXPMASK	equ (1 shl LD_EXPBITS) - 1
LD_EXPBIAS	equ LD_EXPMASK shr 1
LD_EXPMAX	equ LD_EXPMASK - LD_EXPBIAS

FLT_MIN		equ 1.175494351e-38
FLT_MAX		equ 3.402823466e+38
FLT_MAX_10_EXP	equ 38
FLT_MAX_EXP	equ 128

DBL_MAX_EXP	equ 308
DBL_MAX_10_EXP	equ 308
LDBL_MAX_EXP	equ 4096

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
_SW_INEXACT	equ 0x00000001 ; inexact (precision)
_SW_UNDERFLOW	equ 0x00000002 ; underflow
_SW_OVERFLOW	equ 0x00000004 ; overflow
_SW_ZERODIVIDE	equ 0x00000008 ; zero divide
_SW_INVALID	equ 0x00000010 ; invalid
_SW_DENORMAL	equ 0x00080000 ; denormal status bit

_SW_UNEMULATED	equ 0x00000040 ; unemulated instruction
_SW_SQRTNEG	equ 0x00000080 ; square root of a neg number
_SW_STACKOVERFLOW equ 0x00000200 ; FP stack overflow
_SW_STACKUNDERFLOW equ 0x00000400 ; FP stack underflow

;  Floating point error signals and return codes
_FPE_INVALID	equ 0x81
_FPE_DENORMAL	equ 0x82
_FPE_ZERODIVIDE equ 0x83
_FPE_OVERFLOW	equ 0x84
_FPE_UNDERFLOW	equ 0x85
_FPE_INEXACT	equ 0x86
_FPE_UNEMULATED equ 0x87
_FPE_SQRTNEG	equ 0x88
_FPE_STACKOVERFLOW equ 0x8a
_FPE_STACKUNDERFLOW equ 0x8b
_FPE_EXPLICITGEN equ 0x8c ; raise( SIGFPE )

;; Set the FPU control word as cw = (cw & ~unMask) | (unNew & unMask),
;; i.e. change the bits in unMask to have the values they have in unNew,
;; leaving other bits unchanged.

_controlfp	proto __cdecl :UINT, :UINT
_control87	proto __cdecl :UINT, :UINT

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
_copysign proto __cdecl _Number:double, _Sign:double
_chgsign proto __cdecl _X:double
_SIGN_DEFINED equ <>
endif

_logb		proto __cdecl :double
_scalb		proto __cdecl :double, :SDWORD

_finite		proto __cdecl :double
_fpclass	proto __cdecl :double
_isnan		proto __cdecl :double

.pragma list(pop)
