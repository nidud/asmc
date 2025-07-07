; STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strrev proc <usesds> uses si di string:string_t

    ldr     si,string
    ldr     di,string
    mov     dx,di
    mov     al,0
    mov     cx,-1
    repnz   scasb
    cmp     cx,-2
    je      .2
    sub     di,2
    xchg    si,di
    jmp     .1
.0:
    mov     al,esl[di]
    mov     ah,[si]
    mov     [si],al
    mov     esl[di],ah
    inc     di
    dec     si
.1:
    cmp     di,si
    jb      .0
.2:
    mov     ax,dx
    movl    dx,es
    ret

strrev endp

    end
