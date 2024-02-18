; ALLMUL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    .code

ifndef _WIN64
_I8M::
_U8M::
endif

allmul proc watcall a:int64_t, b:int64_t
ifdef _WIN64
    imul    rdx
else
    .if ( !edx && !ecx )

        mul ebx

    .else

        push    eax
        push    edx
        mul     ecx
        mov     ecx,eax
        pop     eax
        mul     ebx
        add     ecx,eax
        pop     eax
        mul     ebx
        add     edx,ecx

    .endif
endif
    ret

allmul endp

ifndef _WIN64
__llmul:: ; PellesC
_allmul::
    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    allmul
    pop     ebx
    ret     16
endif

    end
