; _RCREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcread proc uses rsi rdi rbx rt:TRECT, p:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    movzx   eax,rt.col
    movzx   edx,rt.row
    movzx   ecx,rt.y
    mov     co.X,ax
    mov     co.Y,dx
    mov     rc.Top,cx
    lea     ecx,[rcx+rdx-1]
    mov     rc.Bottom,cx
    movzx   ecx,rt.x
    mov     rc.Left,cx
    lea     eax,[rcx+rax-1]
    mov     rc.Right,ax

    .if ReadConsoleOutputW(_confh, p, co, 0, &rc)

       .return
    .endif

    mov     rc.Bottom,rc.Top
    mov     rdi,p
    movzx   ebx,co.Y
    mov     co.Y,1
    movzx   esi,co.X
    shl     esi,2

    .for ( : ebx : rc.Bottom++, rc.Top++, ebx--, rdi += rsi )

        .break .if !ReadConsoleOutputW(_confh, rdi, co, 0, &rc)
    .endf
    ret

_rcread endp

    end
