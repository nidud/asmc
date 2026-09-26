.pragma list(push, 0)
ifndef __FLTINTRN_INC
define __FLTINTRN_INC

include libc.inc

ifndef __ccall
ifdef _WIN64
define __ccall <fastcall> ; Use fastcall for -elf64
elseifdef __UNIX__
define __ccall <syscall>
else
define __ccall <c>
endif
endif

define _ST_SIGN		0x000001
define _ST_NEGNUM	0x000002
define _ST_NEGEXP	0x000004
define _ST_ISZERO	0x000008
define _ST_ISHEX	0x000010
define _ST_ISNAN	0x000020
define _ST_ISINF	0x000040
define _ST_INVALID	0x000080
define _ST_UNDERFLOW	0x000100
define _ST_OVERFLOW	0x000200
define _ST_DIGITS	0x000400
define _ST_DOT		0x000800
define _ST_E		0x001000 ; 'E' format
define _ST_F		0x002000 ; 'F' format
define _ST_G		0x004000 ; 'G' format
define _ST_CVT		0x008000 ; cvt routine format rules
define _ST_CAPEXP	0x010000 ; 1.0E-10
define _ST_NO_TRUNC	0x020000 ; always provide ndigits in buffer
define _ST_FLOAT	0x040000 ; REAL4
define _ST_DOUBLE	0x080000 ; REAL8
define _ST_LONGDOUBLE	0x100000 ; REAL10
define _ST_QUADFLOAT	0x200000 ; REAL16
define _ST_ALTERNATE	0x400000 ; alternate form requested
define _ST_UNICODE	0x800000


; Half precision - binary16 -- REAL2 (half)

define H_SIGBITS   11
define H_EXPBITS   5
define H_EXPMASK   ((1 shl H_EXPBITS) - 1)
define H_EXPBIAS   (H_EXPMASK shr 1)
define H_EXPMAX	   (H_EXPMASK - H_EXPBIAS)

; Brain Float16 - bfloat16 -- BF16

define BF_SIGBITS  8
define BF_EXPBITS  8
define BF_EXPMASK  ((1 shl BF_EXPBITS) - 1)
define BF_EXPBIAS  (BF_EXPMASK shr 1)
define BF_EXPMAX   (BF_EXPMASK - BF_EXPBIAS)

; Single precision - binary32 -- REAL4 (float)

define F_SIGBITS   24
define F_EXPBITS   8
define F_EXPMASK   ((1 shl F_EXPBITS) - 1)
define F_EXPBIAS   (F_EXPMASK shr 1)
define F_EXPMAX	   (F_EXPMASK - F_EXPBIAS)

; Double precision - binary64 -- REAL8 (double)

define D_SIGBITS   53
define D_EXPBITS   11
define D_EXPMASK   ((1 shl D_EXPBITS) - 1)
define D_EXPBIAS   (D_EXPMASK shr 1)
define D_EXPMAX	   (D_EXPMASK - D_EXPBIAS)

; Long Double precision - binary80 -- REAL10 (long double)

define LD_SIGBITS  64
define LD_EXPBITS  15
define LD_EXPMASK  ((1 shl LD_EXPBITS) - 1)
define LD_EXPBIAS  (LD_EXPMASK shr 1)
define LD_EXPMAX   (LD_EXPMASK - LD_EXPBIAS)

; Quadruple precision - binary128 -- real16 (__float128)

define Q_SIGBITS   113
define Q_EXPBITS   15
define Q_EXPMASK   ((1 shl Q_EXPBITS) - 1)
define Q_EXPBIAS   (Q_EXPMASK shr 1)
define Q_EXPMAX	   (Q_EXPMASK - Q_EXPBIAS)
define Q_DIGITS	   38
define Q_SIGDIG	   49

; Quadruple precision constants

ifndef _MATH_DEFINES_DEFINED
include math_defines.inc
endif

.enum rounding_mode {
    rm_none,
    rm_downward,
    rm_tonearest,
    rm_towardzero,
    rm_upward,
    rm_num_modes
    }


.template EXTFLOAT	    ; extended (134-bit, 128+16) float
    l		uint64_t ?
    h		uint64_t ?
    e		short_t ?
   .ends


.template STRFLT
    mantissa	EXTFLOAT <> ; 128-bit mantissa
    flags	int_t ?	    ; parsing flags
    exponent	int_t ?	    ; exponent of floating point number
    string	string_t ?  ; pointer to buffer or string
   .ends


.template FLTINFO
    ndigits	int_t ?
    scale	int_t ?
    flags	int_t ?
    expchar	int_t ?
    expwidth	int_t ?
    sign	int_t ?
    dec_place	int_t ?
    n1		int_t ?
    nz1		int_t ?
    n2		int_t ?
    nz2		int_t ?
    bufsize	int_t ?
   .ends


.template U128
    union
     i8		sbyte 16 dup(?)
     i16	sword  8 dup(?)
     i32	sdword 4 dup(?)
     i64	sqword 2 dup(?)
     u8		byte  16 dup(?)
     u16	word   8 dup(?)
     u32	dword  4 dup(?)
     u64	qword  2 dup(?)
     u128	oword  ?
    ends
   .ends


; 128-bit unsigned integer functions

__addo		proto __ccall :ptr uint128_t, :ptr uint128_t
__subo		proto __ccall :ptr uint128_t, :ptr uint128_t
__mulo		proto __ccall :ptr uint128_t, :ptr uint128_t, :ptr uint128_t
__divo		proto __ccall :ptr uint128_t, :ptr uint128_t, :ptr uint128_t
__shlo		proto __ccall :ptr uint128_t, :int_t, :int_t
__shro		proto __ccall :ptr uint128_t, :int_t, :int_t
__saro		proto __ccall :ptr uint128_t, :int_t, :int_t

; Convert HALF, float, double, long double, int, __int64, string

__cvtq_h	proto __ccall :ptr half_t, :ptr qfloat_t
__cvtq_ss	proto __ccall :ptr float_t, :ptr qfloat_t
__cvtq_sd	proto __ccall :ptr double_t, :ptr qfloat_t
__cvtq_ld	proto __ccall :ptr ldouble_t, :ptr qfloat_t
__cvth_q	proto __ccall :ptr qfloat_t, :ptr half_t
__cvtss_q	proto __ccall :ptr qfloat_t, :ptr float_t
__cvtsd_q	proto __ccall :ptr qfloat_t, :ptr double_t
__cvtld_q	proto __ccall :ptr qfloat_t, :ptr ldouble_t
__cvta_q	proto __ccall :ptr qfloat_t, :string_t, :ptr string_t

__cvtq_i32	proto __ccall :ptr qfloat_t
__cvtq_i64	proto __ccall :ptr qfloat_t
__cvti32_q	proto __ccall :ptr qfloat_t, :int_t
__cvti64_q	proto __ccall :ptr qfloat_t, :int64_t

; */+-
; Return pointer to A (result)

__mulq		proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__divq		proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__addq		proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__subq		proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__cmpq		proto __ccall A:ptr qfloat_t, B:ptr qfloat_t

__sqrtq		proto __ccall A:ptr qfloat_t

_flttostr	proto __ccall :ptr, :ptr FLTINFO, :string_t, :uint_t
_strtoflt	proto __ccall :string_t
_fltsetflags	proto __ccall :ptr STRFLT, :string_t, :uint_t
_destoflt	proto __ccall :ptr STRFLT, :string_t
_fltunpack	proto __ccall :ptr STRFLT, :ptr
_fltpackfp	proto __ccall :ptr, :ptr STRFLT
_fltscale	proto __ccall :ptr STRFLT
_fltround	proto __ccall :ptr STRFLT
_fltgetrounding proto __ccall
_fltsetrounding proto __ccall :rounding_mode
_fptostr	proto __ccall :string_t, :int_t, :ptr STRFLT

_fltadd		proto __ccall :ptr STRFLT, :ptr STRFLT
_fltsub		proto __ccall :ptr STRFLT, :ptr STRFLT
_fltdiv		proto __ccall :ptr STRFLT, :ptr STRFLT
_fltmul		proto __ccall :ptr STRFLT, :ptr STRFLT

_flttoi		proto __ccall :ptr STRFLT
_flttoi64	proto __ccall :ptr STRFLT
_itoflt		proto __ccall :ptr STRFLT, :int_t
_i64toflt	proto __ccall :ptr STRFLT, :int64_t

_fptrap		proto __cdecl
_cropzeros	proto __cdecl :string_t
_forcdecpt	proto __cdecl :string_t
_fltconvert	proto __cdecl :ptr, :ptr, :int_t, :int_t, :int_t

define _cfltcvt <_cfltcvt_tab>

CALLBACKC(PF0, :ptr, :ptr, :int_t, :int_t, :int_t)
externdef _cfltcvt_tab:PF0
externdef _fltpowtable:EXTFLOAT
externdef qerrno:errno_t

endif

.pragma list(pop)
