; CMPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cmpq() - Compare Quadruple float
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

cmpq proc vectorcall A:real16, B:real16

    movq rax,xmm0
    movhlps xmm0,xmm0
    movq rdx,xmm0
    movq r10,xmm1
    movhlps xmm0,xmm1
    movq rcx,xmm0

    .return 0 .if ( rax == r10 && rcx == rdx )
    .return 1 .ifs ( rdx >= 0 && rcx < 0 )
    .return -1 .ifs ( rdx < 0 && rcx >= 0 )

    .ifs ( rdx < 0 && rcx < 0 )
        .if ( rcx == rdx )
            cmp r10,rax
        .endif
    .elseif ( rdx == rcx )
        cmp rax,r10
    .endif
    sbb eax,eax
    sbb eax,-1
    ret

cmpq endp

    end
