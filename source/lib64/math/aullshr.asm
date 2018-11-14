; AULLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_aullshr::
__ullshr::

    shrd    rax,rdx,cl
    shr     rdx,cl
    test    cl,0xC0
    jnz     @F
    ret
@@:
    test    cl,0x80
    jnz     @F
    mov     rax,rdx
    xor     rdx,rdx
    ret
@@:
    xor     eax,eax
    xor     edx,edx
    ret

    end
