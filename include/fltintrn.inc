.pragma list(push, 0)
ifndef __FLTINTRN_INC
__FLTINTRN_INC equ <>
ifndef __LIBC_INC
 include libc.inc
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
_ST_E		equ 0x1000  ; 'E' format
_ST_F		equ 0x2000  ; 'F' format
_ST_G		equ 0x4000  ; 'G' format
_ST_CVT		equ 0x8000  ; cvt routine format rules
_ST_CAPEXP	equ 0x10000

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

STRFLT		struct
flags		int_t ?		; parsing flags
exponent	int_t ?		; exponent of floating point number
string		string_t ?	; pointer to buffer or string
mantissa	ptr_t ?		; pointer to 128-bit mantissa
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
_fltscale	proto __cdecl :ptr STRFLT
_fptostr	proto __cdecl :string_t, :int_t, :ptr STRFLT

endif

.pragma list(pop)
