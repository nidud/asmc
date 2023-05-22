; WCSCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

wcscmp proc a:wstring_t, b:wstring_t

    ldr     rcx,a
    ldr     rdx,b
    xor     eax,eax
.0:
    xor     ax,[rcx]
    jz      .5
    sub     ax,[rdx]
    jnz     .1
    xor     ax,[rcx+2]
    jz      .4
    sub     ax,[rdx+2]
    jnz     .1
    xor     ax,[rcx+4]
    jz      .3
    sub     ax,[rdx+4]
    jnz     .1
    xor     ax,[rcx+6]
    jz      .2
    sub     ax,[rdx+6]
    jnz     .1
    add     rcx,8
    add     rdx,8
    jmp     .0
.1:
    sbb     rax,rax
    sbb     rax,-1
    jmp     .6
.2:
    add     rdx,2
.3:
    add     rdx,2
.4:
    add     rdx,2
.5:
    sub     ax,[rdx]
    jnz     .1
.6:
    ret

wcscmp endp

    end
