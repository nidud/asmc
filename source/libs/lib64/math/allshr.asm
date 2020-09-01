; ALLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_allshr::

    shrd    rax,rdx,cl
    sar     rdx,cl
    test    cl,0xC0
    jnz     @F
    ret
@@:
    test    cl,0x80
    jnz     @F
    mov     rax,rdx
    sar     rdx,63
    ret
@@:
    xor     eax,eax
    xor     edx,edx
    ret

    end
