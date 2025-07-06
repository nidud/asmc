; STRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strncmp proc uses si di s1:string_t, s2:string_t, count:size_t

    pushl   ds
    mov     cx,count
    test    cx,cx
    jz      .1
    mov     dx,cx
    ldr     di,s1
    mov     si,di
    sub     ax,ax
    repne   scasb
    neg     cx
    add     cx,dx
    mov     di,si
    ldr     si,s2
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
