.pragma list(push, 0)
ifndef __FLTINTRN_INC
define __FLTINTRN_INC
ifndef __LIBC_INC
 include libc.inc
endif

_ST_SIGN	equ 0x000001
_ST_NEGNUM	equ 0x000002
_ST_NEGEXP	equ 0x000004
_ST_ISZERO	equ 0x000008
_ST_ISHEX	equ 0x000010
_ST_ISNAN	equ 0x000020
_ST_ISINF	equ 0x000040
_ST_INVALID	equ 0x000080
_ST_UNDERFLOW	equ 0x000100
_ST_OVERFLOW	equ 0x000200
_ST_DIGITS	equ 0x000400
_ST_DOT		equ 0x000800
_ST_E		equ 0x001000	; 'E' format
_ST_F		equ 0x002000	; 'F' format
_ST_G		equ 0x004000	; 'G' format
_ST_CVT		equ 0x008000	; cvt routine format rules
_ST_CAPEXP	equ 0x010000	; 1.0E-10
_ST_NO_TRUNC	equ 0x020000	; always provide ndigits in buffer
_ST_FLOAT	equ 0x040000	; REAL4
_ST_DOUBLE	equ 0x080000	; REAL8
_ST_LONGDOUBLE	equ 0x100000	; REAL10
_ST_QUADFLOAT	equ 0x200000	; REAL16

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

; Quadruple precision - binary128 -- real16 (__float128)

Q_SIGBITS	equ 113
Q_EXPBITS	equ 15
Q_EXPMASK	equ (1 shl Q_EXPBITS) - 1
Q_EXPBIAS	equ Q_EXPMASK shr 1
Q_EXPMAX	equ Q_EXPMASK - Q_EXPBIAS
Q_DIGITS	equ 38
Q_SIGDIG	equ 49

.enum rounding_mode {
    rm_none,
    rm_downward,
    rm_tonearest,
    rm_towardzero,
    rm_upward,
    rm_num_modes
    }

EXTFLOAT	struct		; extended (134-bit, 128+16) float
l		uint64_t ?
h		uint64_t ?
e		short_t ?
EXTFLOAT	ends

STRFLT		struct
mantissa	EXTFLOAT <>	; 128-bit mantissa
flags		int_t ?		; parsing flags
exponent	int_t ?		; exponent of floating point number
string		string_t ?	; pointer to buffer or string
STRFLT		ends
LPSTRFLT	typedef ptr STRFLT

FLTINFO		struct
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
bufsize		int_t ?
FLTINFO		ends
LPFLTINFO	typedef ptr FLTINFO

_flttostr	proto __cdecl :ptr, :ptr FLTINFO, :string_t, :uint_t
_cqcvt		proto __cdecl :ptr real16, :string_t, :int_t, :int_t, :int_t
_cldcvt		proto __cdecl :ptr real10, :string_t, :int_t, :int_t, :int_t
_cfltcvt	proto __cdecl :ptr real8, :string_t, :int_t, :int_t, :int_t
_strtoflt	proto __cdecl :string_t
_forcdecpt	proto __cdecl :string_t
_cropzeros	proto __cdecl :string_t
_fltsetflags	proto __cdecl :ptr STRFLT, :string_t, :uint_t
_destoflt	proto __cdecl :ptr STRFLT, :string_t
_fltunpack	proto __cdecl :ptr STRFLT, :ptr
_fltpackfp	proto __cdecl :ptr, :ptr STRFLT
_fltscale	proto __cdecl :ptr STRFLT
_fltround	proto __cdecl :ptr STRFLT
_fltgetrounding proto __cdecl
_fltsetrounding proto __cdecl :rounding_mode
_fptostr	proto __cdecl :string_t, :int_t, :ptr STRFLT

_fltadd		proto __cdecl :ptr STRFLT, :ptr STRFLT
_fltsub		proto __cdecl :ptr STRFLT, :ptr STRFLT
_fltdiv		proto __cdecl :ptr STRFLT, :ptr STRFLT
_fltmul		proto __cdecl :ptr STRFLT, :ptr STRFLT
_flttoi		proto __cdecl :ptr STRFLT
_flttoi64	proto __cdecl :ptr STRFLT
_itoflt		proto __cdecl :ptr STRFLT, :int_t
_i64toflt	proto __cdecl :ptr STRFLT, :int64_t


externdef _fltpowtable:EXTFLOAT

endif

.pragma list(pop)
