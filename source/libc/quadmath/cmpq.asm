; CMPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cmpq() - Compare Quadruple float
;
include quadmath.inc

    .code

    option dotname

cmpq proc A:real16, B:real16
ifdef _WIN64
    shufpd  xmm0,xmm0,1
    shufpd  xmm1,xmm1,1
    movq    rcx,xmm0
    movq    rdx,xmm1
    shufpd  xmm0,xmm0,1
    shufpd  xmm1,xmm1,1
    movq    r10,xmm0
    movq    r11,xmm1
    xor     eax,eax
    bt      rdx,63
    jnc     .0
    bt      rcx,63
    jnc     .1
    cmp     rdx,rcx
    jne     .2
    cmp     r11,r10
    jne     .2
    jmp     .3
.0:
    bt      rcx,63
    jc      .b
    cmp     rcx,rdx
    jne     .2
    cmp     r10,r11
    jne     .2
    jmp     .3
.1:
    inc     eax
    jmp     .3
.b:
    dec     rax
    jmp     .3
.2:
    sbb     rax,rax
    sbb     rax,-1
.3:
else
    int 3
endif
    ret

cmpq endp

    end
