ifndef __ISA_AVAILABILITY__H__
define __ISA_AVAILABILITY__H__
include libc.inc

.enum {
    __ISA_AVAILABLE_X86     = 0,
    __ISA_AVAILABLE_SSE2    = 1,
    __ISA_AVAILABLE_SSE42   = 2,
    __ISA_AVAILABLE_AVX     = 3,
    __ISA_AVAILABLE_ENFSTRG = 4,
    __ISA_AVAILABLE_AVX2    = 5,
    __ISA_AVAILABLE_AVX512  = 6,
    __ISA_AVAILABLE_ARMNT   = 0,
    __ISA_AVAILABLE_NEON    = 1,
    __ISA_AVAILABLE_NEON_ARM64 = 2,
    }

define __FAVOR_ATOM    0
define __FAVOR_ENFSTRG 1

externdef __favor:int_t
externdef __isa_available:int_t
externdef __isa_enabled:int_t

endif
