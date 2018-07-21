
include math.inc
include smmintrin.inc

    .code

    option win64:rsp nosave noauto

fmod proc x:double, y:double

    movapd  xmm2,xmm0
    divpd   xmm2,xmm1
    roundpd xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulpd   xmm2,xmm1
    subpd   xmm0,xmm2
    ret

fmod endp

    end
