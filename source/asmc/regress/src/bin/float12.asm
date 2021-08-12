;
; v2.32.63 - option float : default is 4
;
    .686
    .xmm
    .model flat, c

    .code

main proc

    .new float:real4 = 4.0

    .if ( xmm0 > float )
        nop
    .endif
    .if ( xmm0 > 4.0 )
        nop
    .endif

    option float:8

    .new double:real8

    .if ( xmm0 > double )
        nop
    .endif
    .if ( xmm0 > 8.0 )
        nop
    .endif
    ret

main endp

    end
