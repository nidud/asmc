; ROUNDF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

option dotname

    .code

roundf proc x:float
ifdef _WIN64
    movd        eax,xmm0
    and         eax,0x7f800000
    mov         ecx,23
    mov         edx,1
    sar         eax,cl
    sub         eax,0x7e
    jbe         .1
    sub         ecx,eax
    js          .3
    shl         edx,cl
    mov         eax,0xfffffffe
    shl         eax,cl
    movd        xmm2,edx
    movd        xmm3,eax
    cvttps2dq   xmm1,xmm0
    paddd       xmm0,xmm2
    pand        xmm0,xmm3
    jmp         .3
.1:
    je          .2
    mov         eax,0x80000000
    movd        xmm2,eax
    cvttps2dq   xmm1,xmm0
    andps       xmm0,xmm2
    jmp         .3
.2:
    mov         eax,0x00800000
    mov         edx,0xff800000
    movd        xmm2,eax
    movd        xmm3,edx
    cvttps2dq   xmm1,xmm0
    paddd       xmm0,xmm2
    pand        xmm0,xmm3
.3:
else
    mov         eax,x
ifdef __SSE__
    movss       xmm0,x
endif
    and         eax,0x7f800000
    mov         ecx,23
    mov         edx,1
    sar         eax,cl
    sub         eax,0x7e
    jbe         .1
    sub         ecx,eax
    js          .4
    shl         edx,cl
    mov         eax,0xfffffffe
    shl         eax,cl
    add         x,edx
    and         x,eax
    jmp         .3
.1:
    je          .2
    and         x,0x80000000
    jmp         .3
.2:
    add         x,0x00800000
    and         x,0xff800000
.3:
ifdef __SSE__
    cvttps2dq   xmm0,xmm0
endif
.4:
    fld         x
endif
    ret

roundf endp

    end
