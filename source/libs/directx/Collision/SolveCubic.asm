; SOLVECUBIC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXCollision.inc

    .code

SolveCubic proc XM_CALLCONV e:float, f:float, g:float, t:ptr float, u:ptr float, v:ptr float

  local d:float, p:float, h:float, q:float

    movaps  xmm3,xmm0
    movaps  xmm4,xmm1
    mulss   xmm0,xmm0
    mulss   xmm1,xmm3
    divss   xmm1,3.0
    subss   xmm2,xmm1
    movaps  xmm5,xmm0
    divss   xmm5,3.0
    subss   xmm4,xmm5
    movss   xmm5,27.0
    mulss   xmm0,xmm3
    movaps  xmm1,xmm4
    mulss   xmm1,xmm4
    addss   xmm0,xmm0
    divss   xmm0,xmm5
    mulss   xmm1,xmm4
    divss   xmm1,xmm5
    pxor    xmm5,xmm5
    addss   xmm2,xmm0
    movaps  xmm0,xmm2
    mulss   xmm0,xmm2
    mulss   xmm0,2.0
    addss   xmm1,xmm0
    mov     rcx,u
    mov     rdx,v
    movss   xmm4,-0.0
    comiss  xmm1,xmm5
    .ifa
        xor eax,eax
        mov [r9],eax
        mov [rcx],eax
        mov [rdx],eax
        .return
    .endif
    ucomiss xmm1,xmm5
    .ifz
        ucomiss xmm2,xmm5
        .ifz
            xorps xmm3,xmm4
            divss xmm3,3.0
            movss [r9],xmm3
            movss [rcx],xmm3
            movss [rdx],xmm3
            .return 1
        .endif
    .endif

    subss   xmm0,xmm1
    sqrtss  xmm0,xmm0
    movss   p,xmm0
    movss   q,xmm2
    movss   d,xmm3
    comiss  xmm5,xmm0
    .ifa
        xorps   xmm0,xmm4
        powf(xmm0, 1.0 / 3.0)
        movss   xmm1,-0.0
        movaps  xmm5,xmm0
        movaps  xmm6,xmm0
        xorps   xmm5,xmm1
    .else
        powf(xmm0, 1.0 / 3.0)
        movss   xmm1,-0.0
        movaps  xmm6,xmm0
        movaps  xmm5,xmm0
        xorps   xmm6,xmm1
    .endif
    movss   xmm4,p
    movss   xmm0,q
    addss   xmm4,xmm4
    xorps   xmm0,xmm1
    movss   p,xmm6
    movss   q,xmm5
    divss   xmm0, xmm4
    XMScalarACos(xmm0)
    divss   xmm0, 3.0
    movss   h,xmm0
    XMScalarCos(xmm0)
    movss   xmm1,h
    movss   h,xmm0
    XMScalarSin(xmm1)
    movss   xmm5,q
    movss   xmm1,h
    movss   xmm2,0.333333
    movss   xmm6,p
    addss   xmm5,xmm5
    movss   xmm3,d
    divss   xmm3,3.0
    mulss   xmm2,xmm0
    movaps  xmm0,xmm1
    mulss   xmm5,xmm1
    addss   xmm0,xmm2
    subss   xmm1,xmm2
    subss   xmm5,xmm3
    mulss   xmm0,xmm6
    mulss   xmm1,xmm6
    mov     rcx,t
    movss   [rcx],xmm5
    subss   xmm0,xmm3
    subss   xmm1,xmm3
    mov     rcx,u
    mov     rdx,v
    movss   [rcx],xmm0
    movss   [rdx],xmm1
    mov     eax,1
    ret

SolveCubic endp

    end
