; _SCWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scwrite proc uses rsi rbx rect:TRECT, buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    mov     rsi,rdx

    movzx   eax,rect.col
    movzx   ecx,rect.x
    mov     co.x,ax
    mov     rc.Left,cx
    lea     eax,[eax+ecx-1]
    mov     rc.Right,ax
    mov     al,rect.row
    mov     cl,rect.y
    mov     co.y,ax
    mov     rc.Top,cx
    lea     eax,[eax+ecx-1]
    mov     rc.Bottom,ax

    .return .ifd WriteConsoleOutput(hStdOutput, rsi, co, 0, &rc)

    movzx   ebx,co.y
    mov     rc.Bottom,rc.Top
    mov     co.y,1

    .for ( : ebx : ebx--, rc.Bottom++, rc.Top++ )

        .break .ifd !WriteConsoleOutput(hStdOutput, rsi, co, 0, &rc)

        movzx eax,co.x
        shl   eax,2
        add   rsi,rax
    .endf

    xor eax,eax
    cmp ebx,1
    adc eax,0
    ret

_scwrite endp

    end
