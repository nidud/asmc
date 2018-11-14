; SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

sqrtq proc vectorcall Q:XQFLOAT

  local x:U128
  local y:U128

    movaps x,xmm0

    .repeat

        mov     rax,x.m64[0]
        mov     rdx,x.m64[8]
        shld    rcx,rdx,16
        mov     r8,rcx
        and     ecx,Q_EXPMASK
        shl     rdx,16

        .break .if ecx == Q_EXPMASK && !rax && !rdx
        .break .if !ecx && !rax && !rdx

        .if r8d & 0x8000

            subq(xmm0, xmm0)
            divq(xmm0, xmm0)
            .break
        .endif

        movaps y,sqrtqf(xmm0)
        movaps xmm1,divq(x, y)
        subq(y, xmm1)
        movaps xmm1,mulq(xmm0, 0.5)
        subq(y, xmm1)

    .until 1
    ret

sqrtq endp

    end
