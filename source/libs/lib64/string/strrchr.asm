; STRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

strrchr proc string:string_t, chr:int_t

    xor	    eax,eax
@@:
    mov	    dh,[rcx]
    test    dh,dh
    jz	    @F
    cmp	    dh,dl
    cmovz   rax,rcx
    add	    rcx,1
    jmp	    @B
@@:
    ret

strrchr endp

    end
