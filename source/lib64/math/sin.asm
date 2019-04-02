; SIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include libc.inc
include xmmmacros.inc

M_PI equ <3.141592653589793238462643>

    .data
    cosoffs real8 0.0, -M_PI/2.0, 0.0, -M_PI/2.0
    cossign real8 1.0, -1.0, -1.0, 1.0, -0.0, -0.0

    .code

sin::

    movaps  xmm1,xmm0
    mulsd   xmm1,FLT8(0x3fe45f306dc9c883)
    cvttsd2si eax,xmm1
    lea     rcx,[rax-1]

common:

    movaps  xmm2,xmm0
    xorps   xmm1,xmm1
    and     ecx,3
    cvtsi2sd xmm1,eax
    mulsd   xmm1,FLT8(0x3ff921fb54442d18)
    subsd   xmm2,xmm1
    lea     rax,cosoffs
    addsd   xmm2,[rax+rcx*8]
    mulsd   xmm2,xmm2
    lea     rax,cossign
    xorps   xmm2,[rax+4*8]
    movaps  xmm0,xmm2
    mulsd   xmm0,FLT8(0x3ca6827863b97d97)
    addsd   xmm0,FLT8(0x3d2ae7f3e733b81f)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3da93974a8c07c9d)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3e21eed8eff8d898)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3e927e4fb7789f5c)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3efa01a01a01a01a)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3f56c16c16c16c17)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3fa5555555555555)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3fe0000000000000)
    mulsd   xmm0,xmm2
    addsd   xmm0,FLT8(0x3ff0000000000000)
    mulsd   xmm0,[rax+rcx*8]
    ret

cos::

    movaps  xmm1,xmm0
    mulsd   xmm1,FLT8(0x3fe45f306dc9c883)
    cvttsd2si eax,xmm1
    mov     ecx,eax
    jmp     common

    end
