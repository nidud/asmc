; ALLMUL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .486
    .model flat, c
    .code

_I8M::
_U8M::
    .if ( !edx && !ecx )
        mul ebx
        ret
    .endif
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
    ret

__llmul:: ; PellesC
_allmul::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    _U8M
    pop     ebx
    ret     16

    END
