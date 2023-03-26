; _RCFRAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

; Unicode box charcters -- https://www.compart.com/en/unicode/U+2500

define U_LIGHT_HORIZONTAL          0x2500   ; -
define U_LIGHT_VERTICAL            0x2502   ; |
define U_LIGHT_DOWN_AND_RIGHT      0x250C   ; Single corners
define U_LIGHT_DOWN_AND_LEFT       0x2510   ;
define U_LIGHT_UP_AND_RIGHT        0x2514   ;
define U_LIGHT_UP_AND_LEFT         0x2518   ;

define U_LIGHT_VERTICAL_AND_RIGHT  0x251C   ; Insert single corners
define U_LIGHT_VERTICAL_AND_LEFT   0x2524   ;
define U_LIGHT_DOWN_AND_HORIZONTAL 0x252C   ;
define U_LIGHT_UP_AND_HORIZONTAL   0x2534   ;

define U_DOUBLE_HORIZONTAL         0x2550   ; =
define U_DOUBLE_VERTICAL           0x2551   ; ||
define U_DOUBLE_DOWN_AND_RIGHT     0x2554   ; Double corners
define U_DOUBLE_DOWN_AND_LEFT      0x2557   ;
define U_DOUBLE_UP_AND_RIGHT       0x255A   ;
define U_DOUBLE_UP_AND_LEFT        0x255D   ;

define U_LIGHT_ARC_DOWN_AND_RIGHT  0x256D   ; Single rounded corners
define U_LIGHT_ARC_DOWN_AND_LEFT   0x256E   ;
define U_LIGHT_ARC_UP_AND_LEFT     0x256F   ;
define U_LIGHT_ARC_UP_AND_RIGHT    0x2570   ;

.template BoxChars
    Vertical    dw ?
    Horizontal  dw ?
    TopLeft     dw ?
    TopRight    dw ?
    BottomLeft  dw ?
    BottomRight dw ?
   .ends

.code

_rcframe proc uses rsi rdi rbx wz:TRECT, rc:TRECT, wp:PCHAR_INFO, type:int_t, attrib:uchar_t

   .new ft:BoxChars
   .new cols:byte
   .new rows:byte

    ; BoxDrawingTypeSingle

    mov ft.Vertical,    U_LIGHT_VERTICAL
    mov ft.Horizontal,  U_LIGHT_HORIZONTAL

    .switch pascal type
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

    movzx   eax,wz.col
    mul     rc.y
    mov     edi,eax
    movzx   eax,rc.x
    add     edi,eax
    shl     edi,2
    add     rdi,wp

    mov     al,rc.col
    sub     al,2
    mov     cols,al
    mov     al,rc.row
    sub     al,2
    mov     rows,al

    movzx   eax,attrib
    movzx   edx,wz.col
    shl     edx,2
    lea     rbx,[rdi+rdx]
    shl     eax,16
    mov     ax,ft.TopLeft

    .ifnz

        stosd
        mov     ax,ft.Horizontal
        movzx   ecx,cols
        rep     stosd
        mov     ax,ft.TopRight
        stosd
        mov     ax,ft.Vertical
        movzx   ecx,cols

        .for (  : rows : rows-- )

            mov     rdi,rbx
            add     rbx,rdx
            stosd
            mov     [rdi+rcx*4],eax
        .endf

        mov     rdi,rbx
        mov     ax,ft.BottomLeft
        stosd
        mov     ax,ft.Horizontal
        movzx   ecx,cols
        rep     stosd
        mov     ax,ft.BottomRight
        stosd

    .else

        mov     [rdi],ax
        mov     ax,ft.Horizontal
        add     rdi,4

        .for ( cl = 0 : cl < cols : cl++, rdi += 4 )

            mov [rdi],ax
        .endf

        mov     ax,ft.TopRight
        mov     [rdi],ax
        mov     ax,ft.Vertical
        movzx   ecx,cols

        .for ( : rows : rows-- )

            mov rdi,rbx
            add rbx,rdx
            mov [rdi],ax
            mov [rdi+rcx*4+4],ax
        .endf

        mov     rdi,rbx
        mov     ax,ft.BottomLeft
        mov     [rdi],ax
        add     rdi,4
        mov     ax,ft.Horizontal

        .for ( cl = 0 : cl < cols : cl++, rdi += 4 )

            mov [rdi],ax
        .endf
        mov     ax,ft.BottomRight
        mov     [rdi],ax
    .endif
    ret

_rcframe endp

    end
