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

_ST_FLT16	equ 0x4000
_ST_FLT32	equ 0x8000

EXPONENT_BIAS	equ 0x3FFF ; REAL10/16

Q_SIGBITS	equ 112
Q_EXPBITS	equ 15
Q_EXPMASK	equ (1 shl Q_EXPBITS) - 1
Q_EXPMAX	equ Q_EXPMASK - EXPONENT_BIAS
Q_EXPMIN	equ -EXPONENT_BIAS

.xlist

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

_atonf	proto __cdecl :ptr, :ptr, :ptr, :ptr, :dword
_mulfq	proto __cdecl :ptr, :ptr, :ptr
_divfq	proto __cdecl :ptr, :ptr, :ptr
_normalizefq proto __cdecl :ptr, :dword

_lk_mulfq proto __cdecl
_lk_divfq proto __cdecl
_lk_mulqw proto __cdecl

.list
