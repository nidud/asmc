; LABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

labs proc x:int_t
ifndef _WIN64
    mov     ecx,x
endif
    mov     eax,ecx
    neg     eax
    test    ecx,ecx
ifdef __SSE__
    cmovns  eax,ecx
else
    .ifns
        mov eax,ecx
    .endif
endif
    ret
labs endp

    end
