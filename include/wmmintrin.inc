ifndef _INCLUDED_WMM
_INCLUDED_WMM equ <>
.xlist
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: Intel Architecture intrinsic functions not supported in the pure mode>
endif
include nmmintrin.inc

_mm_aesdec_si128		proto __cdecl :oword, :oword
_mm_aesdeclast_si128		proto __cdecl :oword, :oword
_mm_aesenc_si128		proto __cdecl :oword, :oword
_mm_aesenclast_si128		proto __cdecl :oword, :oword
_mm_aesimc_si128		proto __cdecl :oword
_mm_aeskeygenassist_si128	proto __cdecl :oword, :dword
_mm_clmulepi64_si128		proto __cdecl :oword, :oword

.list
endif ;; _INCLUDED_WMM
