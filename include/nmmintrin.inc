ifndef _INCLUDED_NMM
_INCLUDED_NMM equ <>
.xlist

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif
include smmintrin.inc
.xlist

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

_mm_cmpistrm		proto :oword, :oword, :sdword
_mm_cmpistri		proto :oword, :oword, :sdword

_mm_cmpestrm		proto :oword, :sdword, :oword, :sdword, :sdword
_mm_cmpestri		proto :oword, :sdword, :oword, :sdword, :sdword

_mm_cmpistrz		proto :oword, :oword, :sdword
_mm_cmpistrc		proto :oword, :oword, :sdword
_mm_cmpistrs		proto :oword, :oword, :sdword
_mm_cmpistro		proto :oword, :oword, :sdword
_mm_cmpistra		proto :oword, :oword, :sdword

_mm_cmpestrz		proto :oword, :sdword, :oword, :sdword, :sdword
_mm_cmpestrc		proto :oword, :sdword, :oword, :sdword, :sdword
_mm_cmpestrs		proto :oword, :sdword, :oword, :sdword, :sdword
_mm_cmpestro		proto :oword, :sdword, :oword, :sdword, :sdword
_mm_cmpestra		proto :oword, :sdword, :oword, :sdword, :sdword

_mm_cmpgt_epi64		proto :oword, :oword

_mm_popcnt_u32		proto :dword

ifdef _M_X64
_mm_popcnt_u64		proto :qword
endif

_mm_crc32_u8		proto :dword, :byte
_mm_crc32_u16		proto :dword, :word
_mm_crc32_u32		proto :dword, :dword

ifdef _M_X64
_mm_crc32_u64		proto :qword, :qword
endif

endif ;; _INCLUDED_NMM
