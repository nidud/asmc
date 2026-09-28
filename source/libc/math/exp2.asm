; EXP2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
option dotname
.data
 d_tiny     dq 0xfd10000000000000
 d_small    dq 0x3f70000000000000
 d_large    dq 0x011ff00000000000
 d_huge     dq 0x0120cc0000000000
 overflow   dq 0x0120000000000000
endif

.code

exp2 proc x:double
ifdef _WIN64
    movd        rax,xmm0
    movd        rdx,xmm0
    and         rax,g_X2IABSMASK.i1
    sar         rdx,63
    sub         rax,d_small
    add         rdx,64
    cmp         rax,d_large
    jae         .3
.1:
    movapd      xmm1,xmm0
    mulsd       xmm0,4060000000000000r
    cvttsd2si   rax,xmm0
    add         rax,rdx
    mov         rdx,rax
    sar         rax,7
    cvtsi2sd    xmm0,rax
    ucomisd     xmm0,xmm1
    je          .2
    subsd       xmm1,xmm0
    and         rdx,0x7f
    sal         rdx,4
    lea         rcx,g_EXPTABLE
    subsd       xmm1,[rcx+rdx]
    movsd       xmm2,[rcx+rdx+8]
    movlhps     xmm1,xmm1
    movapd      xmm3,xmm1
    addpd       xmm1,{7.73568837260218089745241122384476,-0.538488999896042287022709624001146}
    mulpd       xmm1,xmm3
    mulsd       xmm3,0.133636821875765095445302638781823e-2
    addpd       xmm1,{20.9994886368921956041911010330331,24.6996388387715486518175431533940}
    movhlps     xmm4,xmm1
    mulsd       xmm1,xmm2
    mulsd       xmm3,xmm4
    mulsd       xmm1,xmm3
    addsd       xmm2,xmm1
    movd        xmm0,rax
    psllq       xmm0,52
    paddd       xmm0,xmm2
    jmp         .0
.2:
    add         rax,1023
    movd        xmm0,rax
    psllq       xmm0,52
    jmp         .0
.3:
    jge         .5
    cmp         rax,d_tiny
    jbe         .4
    movapd      xmm1,xmm0
    mulsd       xmm1,0.133335622192926517572920729812647e-2
    addsd       xmm1,0.961813204561913206522420450734562e-2
    mulsd       xmm1,xmm0
    addsd       xmm1,0.555041086648186946112103135980407e-1
    mulsd       xmm1,xmm0
    addsd       xmm1,0.240226506959089504788316195798243
    mulsd       xmm1,xmm0
    addsd       xmm1,0.693147180559945309420618787399210
    mulsd       xmm0,xmm1
    addsd       xmm0,g_X2FONE.f1
    jmp         .0
.4:
    addsd       xmm0,g_X2FONE.f1
    jmp         .0
.5:
    cmp         rax,d_huge
    jae         .7
    xorpd       xmm1,xmm1
    comisd      xmm0,xmm1
    jnc         .8
    movapd      xmm1,xmm0
    mulsd       xmm0,4060000000000000r
    cvttsd2si   rax,xmm0
    add         rax,rdx
    mov         rdx,rax
    sar         rax,7
    cvtsi2sd    xmm0,rax
    ucomisd     xmm0,xmm1
    je          .6
    movsd       xmm5,g_X2FDBLMIN.f1
    mulsd       xmm5,xmm5
    subsd       xmm1,xmm0
    and         rdx,0x7f
    sal         rdx,4
    movsd       xmm0,g_X2FONE.f1
    lea         rcx,g_EXPTABLE
    subsd       xmm1,[rcx+rdx]
    movsd       xmm2,[rcx+rdx+8]
    movlhps     xmm1,xmm1
    movapd      xmm3,xmm1
    addpd       xmm1,{7.73568837260218089745241122384476,-0.538488999896042287022709624001146}
    mulpd       xmm1,xmm3
    mulsd       xmm3,0.133636821875765095445302638781823e-2
    addpd       xmm1,{20.9994886368921956041911010330331,24.6996388387715486518175431533940}
    movhlps     xmm4,xmm1
    mulsd       xmm3,xmm4
    add         rax,1022
    movd        xmm5,rax
    psllq       xmm5,52
    paddd       xmm2,xmm5
    mulsd       xmm1,xmm2
    mulsd       xmm1,xmm3
    movapd      xmm3,xmm2
    addsd       xmm2,xmm0
    movapd      xmm4,xmm2
    subsd       xmm2,xmm0
    subsd       xmm3,xmm2
    addsd       xmm1,xmm3
    addsd       xmm4,xmm1
    xorpd       xmm0,xmm4
    jmp         .0
.6:
    mov         edx,1
    movd        xmm0,rdx
    add         rax,1074
    movd        xmm1,rax
    psllq       xmm0,xmm1
    jmp         .0
.7:
    ucomisd     xmm0,xmm0
    jp          .9
    xorpd       xmm1,xmm1
    comisd      xmm0,xmm1
    jnc         .9
    movsd       xmm1,g_X2INEGINF.i1
    cmpneqsd    xmm1,xmm0
    movsd       xmm0,g_X2FDBLMIN.f1
    andpd       xmm1,xmm0
    mulsd       xmm0,xmm1
    jmp         .0
.8:
    cmp         rax,overflow
    jb          .1
.9:
    mulsd       xmm0,g_X2FDBLMAX.f1
.0:
else
    pow(2.0, x)
endif
    ret
    endp

    end
