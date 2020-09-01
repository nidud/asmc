; ALLSHL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_allshl::
_aullshl::

    shld    rdx,rax,cl
    sal     rax,cl
    test    cl,0xC0
    jnz     @F
    ret
@@:
    test    cl,0x80
    jnz     @F
    mov     rdx,rax
    xor     eax,eax
    ret
@@:
    xor     edx,edx
    xor     eax,eax
    ret

    end
