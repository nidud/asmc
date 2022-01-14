; STRREV.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strrev proc __ctype uses si di string:ptr sbyte

    pushl   ds
    ldsl    si,string
    lesl    di,string
    movl    dx,es
    mov     al,0
    mov     cx,-1
    repnz   scasb
    cmp     cx,-2
    je      .2
    sub     di,2
    xchg    si,di
    jmp     .1
.0:
    mov     al,[di]
    mov     ah,[si]
    mov     [si],al
    mov     [di],ah
    inc     di
    dec     si
.1:
    cmp     di,si
    jb      .0
.2:
    mov     ax,word ptr string
    popl    ds
    ret

strrev endp

    end
