; _SCREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scread proc uses rsi rbx rect:TRECT, buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    mov rsi,buffer

    movzx eax,rect.col
    movzx ecx,rect.x
    mov co.x,ax
    mov rc.Left,cx
    lea eax,[rax+rcx-1]
    mov rc.Right,ax
    mov al,rect.row
    mov cl,rect.y
    mov co.y,ax
    mov rc.Top,cx
    lea eax,[rax+rcx-1]
    mov rc.Bottom,ax

    .ifd ReadConsoleOutput( hStdOutput, rsi, co, 0, &rc )
        .return
    .endif

    movzx ebx,co.y
    mov rc.Bottom,rc.Top
    mov co.y,1

    .for ( : ebx : ebx--, rc.Bottom++, rc.Top++ )

        .break .ifd !ReadConsoleOutput( hStdOutput, rsi, co, 0, &rc )

        movzx eax,co.x
        shl eax,2
        add rsi,rax
    .endf

    xor eax,eax
    cmp ebx,1
    adc eax,0
    ret

_scread endp

    end
