; SSELEVEL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __SSELEVEL_INC
define __SSELEVEL_INC
ifndef __LIBC_INC
 include libc.inc
endif

SSE_MMX                 equ 0x00000001
SSE_SSE                 equ 0x00000002
SSE_SSE2                equ 0x00000004
SSE_SSE3                equ 0x00000008
SSE_SSSE3               equ 0x00000010
SSE_SSE41               equ 0x00000020
SSE_SSE42               equ 0x00000040
SSE_XGETBV              equ 0x00000080
SSE_AVX                 equ 0x00000100
SSE_AVX2                equ 0x00000200
SSE_AVX512F             equ 0x00000400
SSE_AVX512PF            equ 0x00000800
SSE_AVX512ER            equ 0x00001000
SSE_AVX512CD            equ 0x00002000
SSE_AVX512VBMI2         equ 0x00004000
SSE_AVX512PGFNI         equ 0x00008000
SSE_AVX512PVAES         equ 0x00010000
SSE_AVX512PVPCLMULQDQ   equ 0x00020000
SSE_AVX512VNNI          equ 0x00040000
SSE_AVX512BITALG        equ 0x00080000
SSE_AVX512VPOPCNTDQ     equ 0x00100000
SSE_AVX512VP2INTERSECT  equ 0x00200000
SSE_AVX512DQ            equ 0x00400000
SSE_AVX512IFMA          equ 0x00800000
SSE_AVX5124FMAPS        equ 0x01000000
SSE_AVX5124VNNIW        equ 0x02000000
SSE_AVX512VL            equ 0x04000000
SSE_AVX512VBMI          equ 0x08000000
SSE_AVX512BW            equ 0x10000000
SSE_AVX512BF16          equ 0x20000000
SSE_AVXOS               equ 0x40000000

externdef               sselevel:uint_t

setsselevel             proto __cdecl

endif
