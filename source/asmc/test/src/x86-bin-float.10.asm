;
; v2.32.63 - option float : default is 4
; v2.33.02 - added mem2mem operands and auto detect mem-size
;
    .686
    .xmm
    .model flat, c

    .code

main proc

    .new r4_1:real4
    .new r4_2:real4
    .new r8_1:real8
    .new r8_2:real8

    .if (r4_1 > r4_2)
        nop
    .endif
    .if (r8_1 > r8_2)
        nop
    .endif
    .if (xmm0 > r4_2)
        nop
    .endif
    .if (xmm0 > r8_2)
        nop
    .endif
    .if (r4_1 > 4.0)
        nop
    .endif
    .if (r8_1 > 8.0)
        nop
    .endif

    option float: 4 ; default

    .if (xmm0 > 4.0)
        nop
    .endif

    option float: 8

    .if (xmm0 > 8.0)
        nop
    .endif
    ret

main endp

    end
