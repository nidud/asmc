; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

_memicmp::

    push    esi
    push    edi
    mov     esi,[esp+12]
    mov     edi,[esp+16]
    mov     eax,[esp+20]
@@:
    test    eax,eax
    jz      @F

    mov     cl,[esi]
    mov     dl,[edi]
    inc     esi
    inc     edi
    dec     eax
    cmp     cl,dl
    je      @B

    mov     ch,cl
    sub     cl,'a'
    cmp     cl,'Z'-'A'+1
    sbb     cl,cl
    and     cl,'a'-'A'
    xor     cl,ch

    mov     dh,dl
    sub     dl,'a'
    cmp     dl,'Z'-'A'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    xor     dl,dh

    cmp     cl,dl
    je      @B

    sbb     eax,eax
    sbb     eax,-1
@@:
    pop     edi
    pop     esi
    ret

    end

