ifndef __ISA_AVAILABILITY__H__
__ISA_AVAILABILITY__H__ equ <>

ISA_AVAILABILITY        typedef SDWORD
__ISA_AVAILABLE_X86     equ 0
__ISA_AVAILABLE_SSE2    equ 1
__ISA_AVAILABLE_SSE42   equ 2
__ISA_AVAILABLE_AVX     equ 3
__ISA_AVAILABLE_ENFSTRG equ 4
__ISA_AVAILABLE_AVX2    equ 5
__ISA_AVAILABLE_ARMNT   equ 0
__ISA_AVAILABLE_NEON    equ 1

ifdef _M_IX86

__FAVOR_ATOM            equ 0
__FAVOR_ENFSTRG         equ 1

elseifdef _M_AMD64

__FAVOR_ATOM            equ 0
__FAVOR_ENFSTRG         equ 1
__FAVOR_XMMLOOP         equ 2

endif
endif
