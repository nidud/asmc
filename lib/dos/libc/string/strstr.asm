; STRSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc

    .code

strstr proc <usesds> uses bx si di s1:string_t, s2:string_t

    ldr     di,s1
    ldr     si,s2

    mov     cl,[si]
    xor     ax,ax
    cwd
    test    cl,cl
    jz      .3
.0:
    mov     al,esl[di]
    test    al,al
    jz      .3
    inc     di
    cmp     al,cl
    jne     .0
    mov     bx,di
    inc     si
.1:
    mov     al,[si]
    test    al,al
    jz      .2
    cmp     al,esl[bx]
    jne     .2
    inc     si
    inc     bx
    jmp     .1
.2:
    cmp     dl,[si]
    mov     si,word ptr s2
    jne     .0
    mov     ax,di
    dec     ax
    movl    dx,es
.3:
    ret

strstr endp

    end
