
include math.inc

    .code

    option win64:rsp nosave noauto

floor proc x:double

    movq      r10,xmm0
    shr       r10,63
    cvttsd2si rax,xmm0
    sub       rax,r10
    cvtsi2sd  xmm0,rax
    ret

floor endp

    end
