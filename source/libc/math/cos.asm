; COS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _USE_MATH_DEFINES
include math.inc

ifdef _WIN64
option comdat:on
.cdat g_COSSINTABLE(16)
 g_COSSINTABLE real8 0.0, -M_PI_2, 0.0, -M_PI_2, 1.0, -1.0, -1.0, 1.0
endif

.code

cos proc x:double
ifdef _WIN64
    movapd      xmm1,xmm0
    mulsd       xmm1,M_2_PI
    cvttsd2si   eax,xmm1
    cvtsi2sd    xmm1,eax
    mulsd       xmm1,M_PI_2
    subsd       xmm0,xmm1
    and         eax,3
    lea         rcx,g_COSSINTABLE
    addsd       xmm0,[rcx+rax*8]
    mulsd       xmm0,xmm0
    xorpd       xmm0,{-0.0,-0.0}
    movsd       xmm1,xmm0
    mulsd       xmm0,1.561920696858623E-16
    addsd       xmm0,4.779477332387385E-14
    mulsd       xmm0,xmm1
    addsd       xmm0,1.147074559772972E-11
    mulsd       xmm0,xmm1
    addsd       xmm0,2.087675698786810E-09
    mulsd       xmm0,xmm1
    addsd       xmm0,2.755731922398589E-07
    mulsd       xmm0,xmm1
    addsd       xmm0,2.480158730158730E-05
    mulsd       xmm0,xmm1
    addsd       xmm0,1.388888888888889E-03
    mulsd       xmm0,xmm1
    addsd       xmm0,4.166666666666666E-02
    mulsd       xmm0,xmm1
    addsd       xmm0,0.5
    mulsd       xmm0,xmm1
    addsd       xmm0,1.0
    mulsd       xmm0,[rcx+rax*8+4*8]
else
    fld x
    fcos
endif
    ret
    endp

    end
