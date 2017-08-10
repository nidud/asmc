ifndef __LIBC_INC
 include libc.inc
endif
.xlist

; Parsing flags

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

; Quadruple precision - binary128 -- REAL16 (__float128)

Q_SIGBITS	equ 113
Q_EXPBITS	equ 15
Q_EXPMASK	equ (1 shl Q_EXPBITS) - 1
Q_EXPBIAS	equ Q_EXPMASK shr 1
Q_EXPMAX	equ Q_EXPMASK - Q_EXPBIAS

; Octuple precision - binary256 -- REAL32 (__float256)

O_SIGBITS	equ 237
O_EXPBITS	equ 19
O_EXPMASK	equ (1 shl O_EXPBITS) - 1
O_EXPBIAS	equ O_EXPMASK shr 1
O_EXPMAX	equ O_EXPMASK - O_EXPBIAS

_incnd	proto __cdecl :ptr, :dword
_decnd	proto __cdecl :ptr, :dword
_addnd	proto __cdecl :ptr, :ptr, :dword
_subnd	proto __cdecl :ptr, :ptr, :dword
_mulnd	proto __cdecl :ptr, :ptr, :ptr, :dword
_divnd	proto __cdecl :ptr, :ptr, :ptr, :dword
_idivn	proto __cdecl :ptr, :ptr, :ptr, :dword

_cmpnd	proto __cdecl :ptr, :ptr, :dword
_icmpn	proto __cdecl :ptr, :ptr, :dword
_shrnd	proto __cdecl :ptr, :dword, :dword
_sarnd	proto __cdecl :ptr, :dword, :dword
_shlnd	proto __cdecl :ptr, :dword, :dword
_bsfnd	proto __cdecl :ptr, :dword
_bsrnd	proto __cdecl :ptr, :dword
_negnd	proto __cdecl :ptr, :dword
_cpynd	proto __cdecl :ptr, :ptr, :dword
_ndtoa	proto __cdecl :ptr, :ptr, :dword, :dword
_intoa	proto __cdecl :ptr, :ptr, :dword, :dword
_atond	proto __cdecl :ptr, :ptr, :dword, :dword

_cmpow	proto fastcall :ptr, :ptr
_ucmpo	proto fastcall :ptr, :ptr
_mulow	proto __cdecl :ptr, :ptr, :ptr
_divow	proto __cdecl :ptr, :ptr, :ptr
_mulqw	proto __cdecl :qword, :qword, :ptr

_atonf	proto __cdecl :ptr, :ptr, :ptr, :ptr, :dword, :dword, :dword
_mulfq	proto __cdecl :ptr, :ptr, :ptr
_divfq	proto __cdecl :ptr, :ptr, :ptr
_qftod	proto __cdecl :ptr, :ptr
_qftold proto __cdecl :ptr, :ptr
_dtoqf	proto __cdecl :ptr, :qword
_qftol	proto __cdecl :ptr
_qftoll proto __cdecl :ptr
_normalizefq proto __cdecl :ptr, :dword

_lk_mulfq proto __cdecl
_lk_divfq proto __cdecl
_lk_mulqw proto __cdecl

.list
