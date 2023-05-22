; STRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strcmp proc a:string_t, b:string_t

    ldr     rcx,a
    ldr     rdx,b
    xor     eax,eax
.0:
    xor     al,[rcx]
    jz      .5
    sub     al,[rdx]
    jnz     .1
    xor     al,[rcx+1]
    jz      .4
    sub     al,[rdx+1]
    jnz     .1
    xor     al,[rcx+2]
    jz      .3
    sub     al,[rdx+2]
    jnz     .1
    xor     al,[rcx+3]
    jz      .2
    sub     al,[rdx+3]
    jnz     .1
    add     rcx,4
    add     rdx,4
    jmp     .0
.1:
    sbb     rax,rax
    sbb     rax,-1
    jmp     .6
.2:
    add     rdx,1
.3:
    add     rdx,1
.4:
    add     rdx,1
.5:
    sub     al,[rdx]
    jnz     .1
.6:
    ret

strcmp endp

    end
