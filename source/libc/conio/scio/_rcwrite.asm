; _RCWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcwrite proc uses rsi rdi rbx tr:TRECT, p:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    movzx   eax,tr.col
    movzx   edx,tr.row
    movzx   ecx,tr.y
    mov     co.X,ax
    mov     co.Y,dx
    mov     rc.Top,cx
    lea     ecx,[rcx+rdx-1]
    mov     rc.Bottom,cx
    movzx   ecx,tr.x
    mov     rc.Left,cx
    lea     eax,[rcx+rax-1]
    mov     rc.Right,ax

    .if WriteConsoleOutputW(_confh, p, co, 0, &rc)

       .return
    .endif

    mov     rc.Bottom,rc.Top
    mov     rdi,p
    movzx   ebx,co.Y
    mov     co.Y,1
    movzx   esi,co.X
    shl     esi,2

    .for ( : ebx : ebx--, rc.Bottom++, rc.Top++, rdi += rsi )

        .break .if !WriteConsoleOutputW(_confh, rdi, co, 0, &rc)
    .endf
    ret

_rcwrite endp

    end
