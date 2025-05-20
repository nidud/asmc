; ROUND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

option dotname

    .code

round proc x:double
ifdef _WIN64
    movq        rcx,xmm0
    mov         rax,0x7fffffffffffffff
    and         rcx,rax
    movq        xmm2,rax
    mov         rdx,0x4330000000000000
    cmp         rcx,rdx
    jae         .1
    cvttsd2si   rax,xmm0
    andnpd      xmm2,xmm0
    movsd       xmm3,0.5
    cvtsi2sd    xmm1,rax
    subsd       xmm0,xmm1
    orpd        xmm1,xmm2
    xorpd       xmm0,xmm2
    cmpltpd     xmm0,xmm3
    addsd       xmm3,xmm3
    andnpd      xmm0,xmm3
    orpd        xmm0,xmm2
    addsd       xmm0,xmm1
.1:
else
TRUNCATE macro
ifdef __SSE__
    fisttp      x
    fild        x
else
    fnstcw      word ptr x
    mov         dx,word ptr x
    or          word ptr x,0xc00
    fldcw       word ptr x
    frndint
    mov         word ptr x,dx
    fldcw       word ptr x
endif
    endm
    mov         ecx,dword ptr x[4]
    cmp         ecx,0x43300000
    fld         x
    jae         .2
    fld         st(0)
    TRUNCATE
    fxch
    fsub        st(0),st(1)
    fadd        st(0),st(0)
    fld1
    fucomi      st(0),st(1)
    fstp        st(1)
    ja          .1
    fadd        st(1),st(0)
.1:
    fstp        st(0)
    jmp         .4
.2:
    and         ecx,0x7fffffff
    cmp         ecx,0x43300000
    jge         .4
    fabs
    fld         st(0)
    TRUNCATE
    fxch
    fsub        st(0),st(1)
    fadd        st(0),st(0)
    fld1
    fucomi      st(0),st(1)
    fstp        st(1)
    ja          .3
    fadd        st(1),st(0)
.3:
    fstp        st(0)
    fchs
.4:
endif
    ret

round endp

    end
