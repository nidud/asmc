; ABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

abs proc x:SINT

    mov     eax,edi
    neg     eax
    test    edi,edi
    cmovns  eax,edi
    ret

abs endp

    end
