; SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

sqrtq proc q:real16
ifdef _WIN64
    movaps  xmm2,xmm0
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    mov     r8,rcx
    and     ecx,Q_EXPMASK
    shl     rdx,16

    .return .if ( ecx == Q_EXPMASK && !rax && !rdx )
    .return .if ( !ecx && !rax && !rdx )
    .if ( r8d & 0x8000 )
       .return( NAN )
    .endif

    qtofpu( xmm2 )
    fsqrt
    movaps xmm3,fputoq()
    subq( xmm3, divq( xmm2, xmm0 ) )
    subq( xmm3, mulq( xmm0, 0.5 ) )
endif
    ret
sqrtq endp

    end
