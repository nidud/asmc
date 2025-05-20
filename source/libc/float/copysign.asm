; _COPYSIGN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_copysign proc x:double, q:double
ifdef _WIN64
    pcmpeqw xmm2,xmm2
    psrlq   xmm2,1
    andpd   xmm0,xmm2
    andnpd  xmm2,xmm1
    orpd    xmm0,xmm2
else
    mov	    al,byte ptr q[7]
    and	    al,0x80
    and	    byte ptr x[7],0x7F
    or	    byte ptr x[7],al
    fld	    x
endif
    ret

_copysign endp

    end
