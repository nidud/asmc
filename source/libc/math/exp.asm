; EXP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
option dotname
assume uses xmm6 xmm7
.data
 d_tiny  dq 0xfd19d1bd0105c611
 d_small dq 0x3f662e42fefa39ef
 d_large dq 0x011ff4e8de8082e3
 d_huge  dq 0x01211d42457337d4
endif

.code

exp proc x:double
ifdef _WIN64
    movd        rax,xmm0
    movd        rdx,xmm0
    and         rax,g_X2IABSMASK.i1
    sar         rdx,63
    sub         rax,d_small
    add         rdx,64
    cmp         rax,d_large
    ja          .2
.1:
    movapd      xmm1,xmm0
    mulsd       xmm0,40671547652b82fer
    cvttsd2si   rax,xmm0
    add         rax,rdx
    mov         rdx,rax
    sar         rax,7
    and         rdx,0x7f
    sal         rdx,4
    movapd      xmm2,xmm1
    mulsd       xmm1,g_X2FLOG2E.f1
    cvtsi2sd    xmm0,rax
    movapd      xmm7,xmm1
    subsd       xmm1,xmm0
    movapd      xmm4,xmm2
    movsd       xmm3,0fffffffff8000000r
    mulsd       xmm4,03e54ae0bf85ddf44r
    movsd       xmm5,03ff7154760000000r
    lea         rcx,g_EXPTABLE
    subsd       xmm1,[rcx+rdx]
    movsd       xmm6,3f55e52272e0eaecr
    mulsd       xmm6,xmm1
    addsd       xmm6,3f83b2a8abda3d8fr
    mulsd       xmm6,xmm1
    addsd       xmm6,3fac6b08d78310b8r
    andpd       xmm3,xmm2
    subsd       xmm2,xmm3
    mulsd       xmm3,xmm5
    mulsd       xmm2,xmm5
    subsd       xmm3,xmm7
    addsd       xmm2,xmm3
    addsd       xmm2,xmm4
    addsd       xmm2,xmm1
    movapd      xmm3,xmm2
    mulsd       xmm6,xmm2
    mulsd       xmm3,xmm3
    addsd       xmm6,3fcebfbdff82bda7r
    mulsd       xmm2,3fe62e42fefa39efr
    mulsd       xmm3,xmm6
    addsd       xmm2,xmm3
    movd        xmm4,rax
    psllq       xmm4,52
    movsd       xmm0,[rcx+rdx+8]
    mulsd       xmm2,xmm0
    addsd       xmm0,xmm2
    paddd       xmm0,xmm4
    jmp         .9
.2:
    jg          .4
    cmp         rax,d_tiny
    jbe         .3
    movapd      xmm1,xmm0
    mulsd       xmm0,3f8111116e99ac77r
    addsd       xmm0,3fa55555ca407ccbr
    mulsd       xmm0,xmm1
    addsd       xmm0,3fc55555555553f0r
    mulsd       xmm0,xmm1
    addsd       xmm0,3fdffffffffffe1fr
    mulsd       xmm0,xmm1
    addsd       xmm0,g_X2FONE.f1
    mulsd       xmm0,xmm1
    addsd       xmm0,g_X2FONE.f1
    jmp         .9
.3:
    addsd       xmm0,g_X2FONE.f1
    jmp         .9
.4:
    cmp         rax,d_huge
    jg          .5
    xorpd       xmm1,xmm1
    comisd      xmm0,xmm1
    jnc         .6
    movapd      xmm1,xmm0
    mulsd       xmm0,40671547652b82fer
    cvttsd2si   rax,xmm0
    add         rax,rdx
    mov         rdx,rax
    sar         rax,7
    and         rdx,0x7f
    sal         rdx,4
    movsd       xmm6,g_X2FDBLMIN.f1
    mulsd       xmm6,xmm6
    movapd      xmm2,xmm1
    mulsd       xmm1,g_X2FLOG2E.f1
    cvtsi2sd    xmm0,rax
    movapd      xmm7,xmm1
    subsd       xmm1,xmm0
    movapd      xmm4,xmm2
    movsd       xmm3,0fffffffff8000000r
    mulsd       xmm4,03e54ae0bf85ddf44r
    movsd       xmm5,03ff7154760000000r
    movsd       xmm0,g_X2FONE.f1
    lea         rcx,g_EXPTABLE
    subsd       xmm1,[rcx+rdx]
    movsd       xmm6,3f55e52272e0eaecr
    mulsd       xmm6,xmm1
    addsd       xmm6,3f83b2a8abda3d8fr
    mulsd       xmm6,xmm1
    addsd       xmm6,3fac6b08d78310b8r
    andpd       xmm3,xmm2
    subsd       xmm2,xmm3
    mulsd       xmm3,xmm5
    mulsd       xmm2,xmm5
    subsd       xmm3,xmm7
    addsd       xmm2,xmm3
    addsd       xmm2,xmm4
    addsd       xmm2,xmm1
    movapd      xmm3,xmm2
    mulsd       xmm6,xmm2
    mulsd       xmm3,xmm3
    addsd       xmm6,3fcebfbdff82bda7r
    mulsd       xmm2,3fe62e42fefa39efr
    mulsd       xmm3,xmm6
    addsd       xmm2,xmm3
    add         rax,1022
    movd        xmm4,rax
    psllq       xmm4,52
    movsd       xmm1,[rcx+rdx+8]
    paddd       xmm1,xmm4
    mulsd       xmm2,xmm1
    movapd      xmm3,xmm1
    addsd       xmm1,xmm0
    movapd      xmm4,xmm1
    subsd       xmm1,xmm0
    subsd       xmm3,xmm1
    addsd       xmm2,xmm3
    addsd       xmm4,xmm2
    xorpd       xmm0,xmm4
    jmp         .9
.5:
    ucomisd     xmm0,xmm0
    jp          .8
    xorpd       xmm1,xmm1
    comisd      xmm0,xmm1
    jnc         .7
    movsd       xmm1,g_X2INEGINF.i1
    cmpneqsd    xmm1,xmm0
    movsd       xmm0,g_X2FDBLMIN.f1
    andpd       xmm1,xmm0
    mulsd       xmm0,xmm1
    jmp         .9
.6:
    movsd       xmm1,40862e42fefa39efr
    comisd      xmm1,xmm0
    jnc         .1
.7:
    mulsd       xmm0,g_X2FDBLMAX.f1
    jmp         .9
.8:
    addsd       xmm0,xmm0
.9:
else
    fld     x
    fxam
    fstsw   ax
    fwait
    sahf
    jnp     L0
    jnc     L0
    test    ah,2
    jz      L1
    fstp    st
    fldz
    jmp     L1
L0:
    fldl2e
    fmul    st,st(1)
    fst     st(1)
    frndint
    fxch    st(1)
    fsub    st,st(1)
    f2xm1
    fld1
    faddp   st(1),st
    fscale
    fstp    st(1)
L1:
endif
    ret
    endp

    end
