; SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

sqrtq proc vectorcall Q:real16

  local x:__m128i
  local y:__m128i

    movaps  x,xmm0
    mov     rax,x.m128i_u64[0]
    mov     rdx,x.m128i_u64[8]
    shld    rcx,rdx,16
    mov     r8,rcx
    and     ecx,Q_EXPMASK
    shl     rdx,16

    .return .if ecx == Q_EXPMASK && !rax && !rdx
    .return .if !ecx && !rax && !rdx

    .if r8d & 0x8000

        subq(xmm0, xmm0)
        divq(xmm0, xmm0)
        .return
    .endif

    movaps y,sqrtqf(xmm0)
    movaps xmm1,divq(x, y)
    subq(y, xmm1)
    movaps xmm1,mulq(xmm0, 0.5)
    subq(y, xmm1)
    ret

sqrtq endp

    end
