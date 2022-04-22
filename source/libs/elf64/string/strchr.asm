; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strchr proc string:string_t, chr:int_t

    xor	    eax,eax
@@:
    mov	    dh,[rdi]
    test    dh,dh
    jz	    @F
    cmp	    dh,dl
    cmovz   rax,rdi
    lea	    rdi,[rdi+1]
    jnz	    @B
@@:
    ret

strchr endp

    END
