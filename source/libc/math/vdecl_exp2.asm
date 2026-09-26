; VDECL_EXP2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include intrin.inc

.code

ifdef __SSE2__
__vdecl_exp2 proc __vdecl x:XVECTOR
    __vdecl_exp22(_mm_mul_pd(xmm0, g_X2FLOG2E))
    ret
    endp
endif
    end
