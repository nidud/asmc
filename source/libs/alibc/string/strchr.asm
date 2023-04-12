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
    mov	    dl,[rdi]
    test    dl,dl
    jz	    @F
    cmp	    dl,sil
    cmovz   rax,rdi
    lea	    rdi,[rdi+1]
    jnz	    @B
@@:
    ret

strchr endp

    END
