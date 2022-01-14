; STRNCMP.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strncmp proc __ctype uses si di s1:ptr sbyte, s2:ptr sbyte, count:word

    pushl   ds
    mov     cx,count
    test    cx,cx
    jz      .1
    mov     dx,cx
    lesl    di,s1
    mov     si,di
    sub     ax,ax
    repne   scasb
    neg     cx
    add     cx,dx
    mov     di,si
    ldsl    si,s2
    repe    cmpsb
    mov     al,[si-1]
    xor     cx,cx
    cmp     al,esl[di-1]
    ja      .0
    je      .1
    sub     cx,2
.0:
    not     cx
.1:
    mov     ax,cx
    popl    ds
    ret

strncmp endp

    end
