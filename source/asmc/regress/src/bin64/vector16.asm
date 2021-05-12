
    ; 2.31.32
    ; vector(16)

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option casemap:none
    option win64:auto

    .code

main proc

    ; assign vector(16)

    movaps xmm0,{ 1.0 }
    movapd xmm0,{ 1.0, 2.0 }
    movaps xmm0,{ 1.0, 2.0, 3.0, 4.0 }
    movaps xmm0,{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    movdqa xmm0,{ 1 }
    movapd xmm0,{ 1, 2 }
    movups xmm0,{ 1, 2, 3, 4 }
    movaps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8 }
    movupd xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }

    ; use vector(16)

    divpd xmm0,{ 1.0 }
    addpd xmm0,{ 1.0, 2.0 }
    xorpd xmm0,{ 1.0, 2.0, 3.0, 4.0 }
    mulpd xmm0,{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    divps xmm0,{ 1 }
    addps xmm0,{ 1, 2 }
    xorps xmm0,{ 1, 2, 3, 4 }
    mulps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8 }
    subps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }

    ; return vector(16)

    .return { 1.0 }
    .return { 1.0, 2.0 }
    .return { 1.0, 2.0, 3.0, 4.0 }
    .return { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    .return { 1 }
    .return { 1, 2 }
    .return { 1, 2, 3, 4 }
    .return { 1, 2, 3, 4, 5, 6, 7, 8 }
    .return { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }
    ret

main endp

    end
