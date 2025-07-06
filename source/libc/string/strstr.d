; STRSTR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strstr proc uses bx si di s1:string_t, s2:string_t

    pushl   ds
    lesl    di,s1
    movl    dx,es
    ldsl    si,s2
    cmp     BYTE PTR [si],0
    je      .5
.0:
    mov     ah,[si]
.1:
    mov     al,esl[di]
    test    al,al
    jz      .5
    inc     di
    cmp     al,ah
    jne     .1
    mov     bx,di
    inc     si
.2:
    mov     al,[si]
    test    al,al
    jz      .3
    cmp     esl[bx],al
    jne     .3
    inc     si
    inc     bx
    jmp     .2
    dec     si
.3:
    cmp     BYTE PTR [si],0
    mov     si,WORD PTR s2
    jne     .0
    mov     ax,di
    dec     ax
.4:
    popl    ds
    ret
.5:
    xor     ax,ax
    movl    dx,ax
    jmp     .4

strstr endp

    end
