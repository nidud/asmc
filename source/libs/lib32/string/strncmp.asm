; STRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

strncmp::

    push    esi
    mov     edx,[esp+8]
    mov     esi,[esp+12]
    mov     ecx,[esp+16]
    test    ecx,ecx
    jz      .2
.0: mov     al,[edx]
    cmp     al,[esi]
    jne     .1
    inc     esi
    inc     edx
    test    al,al
    je      .2
    dec     ecx
    jnz     .0
.2: xor     eax,eax
    pop     esi
    ret
.1: sbb     eax,eax
    sbb     eax,-1
    pop     esi
    ret

    end
