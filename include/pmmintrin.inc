ifndef _INCLUDED_PMM
define _INCLUDED_PMM
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

_mm_addsub_ps macro a, b
	addsubps a,b
	retm<a>
	endm
_mm_hadd_ps macro a, b
	haddps a,b
	retm<a>
	endm
_mm_hsub_ps macro a, b
	hsubps a,b
	retm<a>
	endm
_mm_movehdup_ps macro a
	movshdup a,a
	retm<a>
	endm
_mm_moveldup_ps macro a
	movsldup a,a
	retm<a>
	endm

_mm_addsub_pd macro a, b
	addsubpd a,b
	retm<a>
	endm
_mm_hadd_pd macro a, b
	haddpd a,b
	retm<a>
	endm
_mm_hsub_pd macro a, b
	hsubpd a,b
	retm<a>
	endm
_mm_loaddup_pd macro a
	movddup a,a
	retm<a>
	endm
_mm_movedup_pd macro a
	movddup a,a
	retm<a>
	endm

_mm_lddqu_si128 macro mem_addr
	lddqu xmm0,mem_addr
	retm<xmm0>
	endm

_mm_monitor macro p, extensions, hints
	mov ecx,extensions
	mov edx,hints
	mov rax,p
	monitor
	retm<>
	endm

_mm_mwait macro extensions, hints
	mov ecx,extensions
	mov eax,hints
	mwait
	retm<>
	endm

.pragma list(pop)
endif
