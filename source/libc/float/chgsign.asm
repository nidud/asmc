; _CHGSIGN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_chgsign proc x:double
ifdef _WIN64
    pcmpeqw xmm1,xmm1
    psllq   xmm1,63
    xorpd   xmm0,xmm1
else
    xor byte ptr x[7],0x80
    fld x
endif
    ret

_chgsign endp

    end
