
    ; inline id > 32 byte

    .x64
    .model flat, fastcall
    .code

    option casemap:none
    option win64:auto

.template D2D1_HWND_RENDER_TARGET_PROPERTIES

    a dd ?
    b dd ?
    c dd ?
    d dd ?

    .inline D2D1_HWND_RENDER_TARGET_PROPERTIES :abs=<0>, :abs=<1>, :abs=<2>, :abs=<3>, :vararg {
        mov this.a,_1
        mov this.b,_2
        mov this.c,_3
        mov this.d,_4
        }
    .ends
    .code

main proc

    .new b:D2D1_HWND_RENDER_TARGET_PROPERTIES(4)
    ret

main endp

    end
