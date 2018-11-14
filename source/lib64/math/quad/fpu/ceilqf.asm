; CEILQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ceilqf proc vectorcall Q:XQFLOAT

  local x:REAL10, w:WORD, n:WORD

    XQFLOATTOLD(x)

    fld     x
    fstcw   w
    fclex
    mov     n,0x0B63
    fldcw   n
    frndint
    fclex
    fldcw   w
    fstp    x

    LDTOXQFLOAT(x)
    ret

ceilqf endp

    end
