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

_scframe proc uses rbx rc:TRECT, type:SINT, at:WORD

   .new ft:BoxChars
    mov ebx,edx
    shl ebx,16

    ; BOX_SINGLE

    mov ft.Vertical,    U_LIGHT_VERTICAL
    mov ft.Horizontal,  U_LIGHT_HORIZONTAL

    .switch pascal esi
    .case BOX_CLEAR
        lea rdi,ft
        mov ecx,sizeof(ft) / 2
        mov eax,' '
        rep stosw
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

    mov bx,ft.TopLeft
    _scputw(rc.x, rc.y, 1, ebx)

    mov bx,ft.Horizontal
    mov dil,rc.x
    mov dl,rc.col
    sub dl,2
    inc dil
    _scputw(dil, rc.y, dl, ebx)

    mov bx,ft.TopRight
    mov dil,rc.x
    add dil,rc.col
    dec dil
    _scputw(dil, rc.y, 1, ebx)

    mov bx,ft.Vertical
    sub rc.row,2
    .for ( rc.y++ : rc.row : rc.row--, rc.y++ )

        _scputw(rc.x, rc.y, 1, ebx)
        mov dil,rc.x
        add dil,rc.col
        dec dil
        _scputw(dil, rc.y, 1, ebx)
    .endf

    mov bx,ft.BottomLeft
    _scputw(rc.x, rc.y, 1, ebx)

    mov bx,ft.Horizontal
    mov dil,rc.x
    mov dl,rc.col
    sub dl,2
    inc dil
    _scputw(dil, rc.y, dl, ebx)

    mov bx,ft.BottomRight
    mov dil,rc.x
    add dil,rc.col
    dec dil
    _scputw(dil, rc.y, 1, ebx)
    ret

_scframe endp

    end
