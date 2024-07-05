; CVTSIQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvtsiq() - __int128 to Quadruple float
;
include quadmath.inc

    .code

    option dotname

cvtsiq proc i:ptr int128_t

ifdef _WIN64

    ldr     rcx,i

    mov     rdx,[rcx+8]
    mov     rax,[rcx]
    mov     r8d,Q_EXPBIAS
    test    rdx,rdx     ; if number is negative
    jns     .0
    neg     rdx         ; negate number
    neg     rax
    sbb     rdx,0
    or      r8d,0x8000
.0:
    mov     rcx,rax
    or      rcx,rdx
    jz      .4
    xor     ecx,ecx
    test    rdx,rdx     ; find most significant non-zero bit
    jz      .1
    bsr     rcx,rdx
    add     ecx,64
    jmp     .2
.1:
    bsr     rcx,rax
.2:
    mov     ch,cl       ; shift bits into position
    mov     cl,127
    sub     cl,ch
    cmp     cl,64
    jb      .3
    sub     cl,64
    mov     rdx,rax
    xor     eax,eax
.3:
    shld    rdx,rax,cl
    shl     rax,cl
    shr     ecx,8       ; get shift count
    add     ecx,r8d     ; calculate exponent
.4:
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1   ; return result
else
    int     3
endif
    ret

cvtsiq endp

    end
