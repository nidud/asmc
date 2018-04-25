.pragma list(push, 0)

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

MAX_LD_DIGITS	equ 22
MAX_LD_HEXDIG	equ 16
MAX_LD_SIGDIG	equ 32
MAX_LD_MANT	equ 64

EXPONENT_BIAS	equ 0x3FFF ; REAL10/REAL16

S_STRFLT	STRUC
flags		dd ?	; parsing flags
exponent	dd ?	; exponent of floating point number
string		LPSTR ? ; pointer to buffer or string
mantissa	PVOID ? ; pointer to mantissa
S_STRFLT	ENDS

LPSTRFLT	typedef ptr S_STRFLT
LPDOUBLE	typedef ptr REAL8
LPLONGDOUBLE	typedef ptr REAL8

_strtoflt	proto __cdecl :LPSTR
_cfltcvt	proto __cdecl :LPDOUBLE, :LPSTR, :SINT, :SINT, :SINT
_cldcvt		proto __cdecl :LPLONGDOUBLE, :LPSTR, :SINT, :SINT, :SINT
_forcdecpt	proto __cdecl :LPSTR
_cropzeros	proto __cdecl :LPSTR
_fltsetflags	proto __cdecl :LPSTRFLT, :LPSTR, :UINT
_destoflt	proto __cdecl :LPSTRFLT, :LPSTR
_hextoflt	proto __cdecl :LPSTRFLT, :LPSTR
_fltscale	proto __cdecl :LPSTRFLT

_qcvt		proto __cdecl :ptr, :LPSTR, :SINT, :SINT, :SINT
_dcvt		proto __cdecl :ptr, :LPSTR, :SINT, :SINT, :SINT
_ldcvt		proto __cdecl :ptr, :LPSTR, :SINT, :SINT, :SINT

.pragma list(pop)
