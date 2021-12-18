; STRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

strcmp::

    mov     edx,[esp+4]
    mov     ecx,[esp+8]
    mov     eax,1
@@:
    test    al,al
    jz      @F
    mov     al,[edx]
    inc     ecx
    inc     edx
    cmp     al,[ecx-1]
    je      @B
    sbb     eax,eax
    sbb     eax,-1
@@:
    ret

    end
