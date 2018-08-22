ifndef __INTRIN0_H_
__INTRIN0_H_ equ <>
if defined(_M_IX86) and not defined(_CHPE_ONLY_)
__MACHINEX86 equ <>
endif
ifdef _M_X64
__MACHINEX64 equ <>
endif
if (defined(_M_IX86) OR defined(_M_X64)) and not defined(_CHPE_ONLY_)
__MACHINEX86_X64 equ <>
endif
endif
