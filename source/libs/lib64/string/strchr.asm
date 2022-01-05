; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

strchr proc string:string_t, chr:int_t

    xor	    eax,eax
@@:
    mov	    dh,[rcx]
    test    dh,dh
    jz	    @F
    cmp	    dh,dl
    cmovz   rax,rcx
    lea	    rcx,[rcx+1]
    jnz	    @B
@@:
    ret

strchr endp

    END
