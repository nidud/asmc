; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

memcmp::

    push    esi
    push    edi
    mov     edi,[esp+12]
    mov     esi,[esp+16]
    mov     ecx,[esp+20]
    xor     eax,eax
    repe    cmpsb
    je      @F
    sbb     eax,eax
    sbb     eax,-1
@@:
    pop     edi
    pop     esi
    ret

    end
