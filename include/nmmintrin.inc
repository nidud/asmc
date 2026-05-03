ifndef _INCLUDED_NMM
define _INCLUDED_NMM
.pragma list(push, 0)
ifndef _LIBC_
include libc.inc
endif
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif
include smmintrin.inc

_SIDD_UBYTE_OPS		equ 0x00
_SIDD_UWORD_OPS		equ 0x01
_SIDD_SBYTE_OPS		equ 0x02
_SIDD_SWORD_OPS		equ 0x03

_SIDD_CMP_EQUAL_ANY	equ 0x00
_SIDD_CMP_RANGES	equ 0x04
_SIDD_CMP_EQUAL_EACH	equ 0x08
_SIDD_CMP_EQUAL_ORDERED equ 0x0C

_SIDD_POSITIVE_POLARITY equ 0x00
_SIDD_NEGATIVE_POLARITY equ 0x10
_SIDD_MASKED_POSITIVE_POLARITY equ 0x20
_SIDD_MASKED_NEGATIVE_POLARITY equ 0x30

_SIDD_LEAST_SIGNIFICANT equ 0x00
_SIDD_MOST_SIGNIFICANT	equ 0x40

_SIDD_BIT_MASK		equ 0x00
_SIDD_UNIT_MASK		equ 0x40

_mm_cmpistrm macro a, b, i
	pcmpistrm a,b,i
	retm<a>
	endm
_mm_cmpistri macro a, b, i
	pcmpistri a,b,i
	retm<a>
	endm

_mm_cmpestrm macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<a>
	endm
_mm_cmpestri macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestri a,b,i
	retm<ecx>
	endm

_mm_cmpistrz macro a, b, i
	pcmpistrm a,b,i
	retm<ZERO?>
	endm
_mm_cmpistrc macro a, b, i
	pcmpistrm a,b,i
	retm<CARRY?>
	endm
_mm_cmpistrs macro a, b, i
	pcmpistrm a,b,i
	retm<SIGN?>
	endm
_mm_cmpistro macro a, b, i
	pcmpistrm a,b,i
	retm<OVERFLOW?>
	endm
_mm_cmpistra macro a, b, i
	pcmpistrm a,b,i
	retm<!CARRY? && !ZERO?>
	endm

_mm_cmpestrz macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<ZERO?>
	endm
_mm_cmpestrc macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<CARRY?>
	endm
_mm_cmpestrs macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<SIGN?>
	endm
_mm_cmpestro macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<OVERFLOW?>
	endm
_mm_cmpestra macro a, la, b, lb, i
	mov eax,la
	mov edx,lb
	pcmpestrm a,b,i
	retm<!CARRY? && !ZERO?>
	endm

_mm_cmpgt_epi64 macro a, b
	pcmpgtq a,b
	retm<a>
	endm

_mm_popcnt_u32 macro a, b
    ifnb <b>
	popcnt a,b
    else
	popcnt a,a
    endif
	retm<a>
	endm
ifdef _M_X64
_mm_popcnt_u64 macro a, b
	exitm<_mm_popcnt_u32(a,b)>
	endm
endif

_mm_crc32_u8 macro crc, v
	crc32 crc,v
	retm<crc>
	endm
_mm_crc32_u16 macro crc, v
	exitm<_mm_crc32_u8(crc, v)>
	endm
_mm_crc32_u32 macro crc, v
	exitm<_mm_crc32_u8(crc, v)>
	endm
ifdef _M_X64
_mm_crc32_u64 macro crc, v
	exitm<_mm_crc32_u8(crc, v)>
	endm
endif

.pragma list(pop)
endif
