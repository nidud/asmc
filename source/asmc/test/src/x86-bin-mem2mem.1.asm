
    ; 2.32.37

    .686
    .xmm
    .model flat, c
    .code


foo proc

  local a:qword, b:qword

    add a,b
    sub a,b
    mov a,b
    cmp a,b

    movq    xmm0,3FF0000000000000r
    movsd   xmm0,1.0
    addsd   xmm0,1.0
    subsd   xmm0,1.0
    mulsd   xmm0,1.0
    divsd   xmm0,1.0
    comisd  xmm0,1.0
    ucomisd xmm0,4.0 / 2.0 - 1.0

    movd    xmm0,3F800000r
    movss   xmm0,1.0
    addss   xmm0,1.0
    subss   xmm0,1.0
    mulss   xmm0,1.0
    divss   xmm0,1.0
    comiss  xmm0,1.0
    ucomiss xmm0,4.0 / 2.0 - 1.0
    ret

foo endp

    end
