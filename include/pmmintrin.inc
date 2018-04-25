ifndef _INCLUDED_PMM
_INCLUDED_PMM equ <>
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif
include emmintrin.inc

_MM_DENORMALS_ZERO_MASK equ 0x0040
_MM_DENORMALS_ZERO_ON	equ 0x0040
_MM_DENORMALS_ZERO_OFF	equ 0x0000

_MM_SET_DENORMALS_ZERO_MODE macro mode
	exitm<_mm_setcsr((_mm_getcsr() and not _MM_DENORMALS_ZERO_MASK) or (mode))>
	endm

_MM_GET_DENORMALS_ZERO_MODE macro
	exitm<(_mm_getcsr() and _MM_DENORMALS_ZERO_MASK)>
	endm

_mm_addsub_ps	proto :oword, :oword
_mm_hadd_ps	proto :oword, :oword
_mm_hsub_ps	proto :oword, :oword
_mm_movehdup_ps proto :oword
_mm_moveldup_ps proto :oword

_mm_addsub_pd	proto :oword, :oword
_mm_hadd_pd	proto :oword, :oword
_mm_hsub_pd	proto :oword, :oword
_mm_loaddup_pd	proto :ptr
_mm_movedup_pd	proto :oword

_mm_lddqu_si128 proto :oword

_mm_monitor	proto :ptr, :dword, :dword
_mm_mwait	proto :dword, :dword

endif
