
include quadmath.inc

    .code

    option win64:rsp nosave noauto

copysignq proc vectorcall number:XQFLOAT, _sign:XQFLOAT

    mov     rax,0x7FFFFFFFFFFFFFFF
    movq    xmm2,rax
    shufps  xmm2,xmm2,01000000B
    andps   xmm0,xmm2
    andnps  xmm2,xmm1
    orps    xmm0,xmm2
    ret

copysignq endp

    end
