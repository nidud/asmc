
include math.inc

    .code

    option win64:rsp nosave noauto

ceil proc x:double

    mov       r11,-0.0
    movq      r10,xmm0
    xor       r10,r11
    movq      xmm0,r10
    shr       r10,63
    cvttsd2si rax,xmm0
    sub       rax,r10
    neg       rax
    cvtsi2sd  xmm0,rax
    ret

ceil endp

    end
