; CVTQ_LD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

cvtq_ld proc q:real16

    xor     r8d,r8d
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    r8,rdx,16
    shld    rdx,rax,16

    mov     eax,r8d
    and     eax,LD_EXPMASK
    neg     eax
    mov     rax,rdx
    rcr     rax,1

    ;; round result

    .ifc
        .if rax == -1
            mov rax,0x8000000000000000
            inc r8w
        .else
            add rax,1
        .endif
    .endif

    movq xmm0,rax
    movd xmm1,r8d
    movlhps xmm0,xmm1
    ret

cvtq_ld endp

    end
