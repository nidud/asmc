; EXP2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

exp2 proc x:double
ifdef _WIN64
    pow(2.0, xmm0)
else
    pow(2.0, x)
endif
    ret

exp2 endp

    end
