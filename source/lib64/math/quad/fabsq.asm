
include quadmath.inc

    .code

    option win64:rsp nosave noauto

fabsq proc vectorcall Q:XQFLOAT

    mov     rax,0x7FFFFFFFFFFFFFFF
    movq    xmm1,rax
    shufps  xmm1,xmm1,01000000B
    andps   xmm0,xmm1
    ret

fabsq endp

    end
