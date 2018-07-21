
include quadmath.inc

    .code

floorqf proc vectorcall Q:XQFLOAT

  local x:REAL10, w:WORD, n:WORD

    XQFLOATTOLD(x)

    fld     x
    fstcw   w
    fclex
    mov     n,0x0763
    fldcw   n
    frndint
    fclex
    fldcw   w
    fstp    x

    LDTOXQFLOAT(x)
    ret

floorqf endp

    end
