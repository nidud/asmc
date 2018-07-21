
include quadmath.inc

    .code

    option win64:rsp nosave noauto

nanq proc vectorcall

    mov     rax,0x7FFF000000000001
    movq    xmm0,rax
    shufps  xmm0,xmm0,01101000B
    ret

nanq endp

    end
