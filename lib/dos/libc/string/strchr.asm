; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strchr proc <usesds> uses si s1:string_t, char:int_t

    ldr     si,s1
    xor     ax,ax
    movl    dx,ax
.0:
    mov     al,[si]
    test    al,al
    jz      .1
    inc     si
    cmp     al,BYTE PTR char
    jne     .0
    movl    dx,ds
    mov     ax,si
    dec     ax
.1:
    ret

strchr endp

    end
