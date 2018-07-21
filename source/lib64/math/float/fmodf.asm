
include math.inc
include smmintrin.inc

    .code

    option win64:rsp nosave noauto

fmodf proc x:float, y:float

    movss   xmm2,xmm0
    divss   xmm2,xmm1
    roundss xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulss   xmm2,xmm1
    subss   xmm0,xmm2
    ret

fmodf endp

    end
