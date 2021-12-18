; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

strcat::

    mov     edx,[esp+4]
    xor     eax,eax
    or      ecx,-1
    xchg    edx,edi
    repnz   scasb
    dec     edi
    xchg    edx,edi
    mov     ecx,[esp+8]
@@:
    mov     al,[ecx]
    mov     [edx],al
    inc     ecx
    inc     edx
    test    al,al
    jnz     @B
    mov     eax,[esp+4]
    ret

    end
