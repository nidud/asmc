; _SCFRAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.template BoxChars
    Vertical    dw ?
    Horizontal  dw ?
    TopLeft     dw ?
    TopRight    dw ?
    BottomLeft  dw ?
    BottomRight dw ?
   .ends

.code

_scframe proc rc:TRECT, type:SINT, attrib:WORD

   .new ft:BoxChars
   .new cols:byte
   .new rows:byte
   .new ci:CHAR_INFO = {0}
   .new x:byte

    mov ci.Attributes,attrib

    ; BOX_SINGLE

    mov ft.Vertical,    U_LIGHT_VERTICAL
    mov ft.Horizontal,  U_LIGHT_HORIZONTAL

    .switch pascal type
    .case BOX_CLEAR
        mov rdx,rdi
        lea rdi,ft
        mov ecx,sizeof(ft) / 2
        mov eax,' '
        rep stosw
        mov rdi,rdx
    .case BOX_DOUBLE
        mov ft.Vertical,    U_DOUBLE_VERTICAL
        mov ft.Horizontal,  U_DOUBLE_HORIZONTAL
        mov ft.TopLeft,     U_DOUBLE_DOWN_AND_RIGHT
        mov ft.TopRight,    U_DOUBLE_DOWN_AND_LEFT
        mov ft.BottomLeft,  U_DOUBLE_UP_AND_RIGHT
        mov ft.BottomRight, U_DOUBLE_UP_AND_LEFT
    .case BOX_SINGLE_VERTICAL
        mov ft.TopLeft,     U_LIGHT_DOWN_AND_HORIZONTAL
        mov ft.TopRight,    U_LIGHT_DOWN_AND_HORIZONTAL
        mov ft.BottomLeft,  U_LIGHT_UP_AND_HORIZONTAL
        mov ft.BottomRight, U_LIGHT_UP_AND_HORIZONTAL
    .case BOX_SINGLE_HORIZONTAL
        mov ft.TopLeft,     U_LIGHT_VERTICAL_AND_RIGHT
        mov ft.TopRight,    U_LIGHT_VERTICAL_AND_LEFT
        mov ft.BottomLeft,  U_LIGHT_VERTICAL_AND_RIGHT
        mov ft.BottomRight, U_LIGHT_VERTICAL_AND_LEFT
    .case BOX_SINGLE_ARC
        mov ft.TopLeft,     U_LIGHT_ARC_DOWN_AND_RIGHT
        mov ft.TopRight,    U_LIGHT_ARC_DOWN_AND_LEFT
        mov ft.BottomLeft,  U_LIGHT_ARC_UP_AND_RIGHT
        mov ft.BottomRight, U_LIGHT_ARC_UP_AND_LEFT
    .default
        mov ft.TopLeft,     U_LIGHT_DOWN_AND_RIGHT
        mov ft.TopRight,    U_LIGHT_DOWN_AND_LEFT
        mov ft.BottomLeft,  U_LIGHT_UP_AND_RIGHT
        mov ft.BottomRight, U_LIGHT_UP_AND_LEFT
    .endsw

    mov ci.Char.UnicodeChar,ft.TopLeft
    _scputw(rc.x, rc.y, 1, ci)
    mov ci.Char.UnicodeChar,ft.Horizontal
    mov al,rc.x
    mov dl,rc.col
    sub dl,2
    inc al
    mov x,al
    _scputw(x, rc.y, dl, ci)
    mov ci.Char.UnicodeChar,ft.TopRight
    mov al,rc.x
    add al,rc.col
    dec al
    mov x,al
    _scputw(x, rc.y, 1, ci)
    mov ci.Char.UnicodeChar,ft.Vertical
    sub rc.row,2
    .for ( rc.y++  : rc.row : rc.row--, rc.y++ )

        _scputw(rc.x, rc.y, 1, ci)
        mov al,rc.x
        add al,rc.col
        dec al
        mov x,al
        _scputw(x, rc.y, 1, ci)
    .endf
    mov ci.Char.UnicodeChar,ft.BottomLeft
    _scputw(rc.x, rc.y, 1, ci)
    mov ci.Char.UnicodeChar,ft.Horizontal
    mov al,rc.x
    mov dl,rc.col
    sub dl,2
    inc al
    mov x,al
    _scputw(x, rc.y, dl, ci)
    mov ci.Char.UnicodeChar,ft.BottomRight
    mov al,rc.x
    add al,rc.col
    dec al
    mov x,al
    _scputw(x, rc.y, 1, ci)
    ret

_scframe endp

    end
