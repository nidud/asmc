; ABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

abs proc x:int_t

    ldr     ecx,x

    mov     eax,ecx
    neg     eax
ifdef __SSE__
    cmovs   eax,ecx
else
    .ifs
        mov eax,ecx
    .endif
endif
    ret

abs endp

    end
