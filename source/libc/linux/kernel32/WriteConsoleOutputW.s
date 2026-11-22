; WRITECONSOLEOUTPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include conio.inc

__conwrite_span proto WINAPI :HANDLE, :PCHAR_INFO, :int_t, :int_t, :int_t

.code

 WriteConsoleOutputW proc WINAPI uses rsi rdi rbx fp:HANDLE, lpBuffer:PCHAR_INFO,
        dwBufferSize:COORD, dwBufferCoord:COORD, lpWriteRegion:PSMALL_RECT
   .new x:int_t
   .new y:int_t
   .new rows:int_t
   .new cols:int_t
   .new stride:size_t
   .new ci:CONSOLE_CURSOR_INFO
    ldr rbx,lpBuffer
    mov rcx,lpWriteRegion
    .if ( !rbx || !rcx )
        .return( 0 )
    .endif
    movzx eax,[rcx].SMALL_RECT.Left
    mov x,eax
    movzx edx,[rcx].SMALL_RECT.Right
    sub edx,eax
    inc edx
    mov cols,edx
    movzx eax,[rcx].SMALL_RECT.Top
    mov y,eax
    movzx edx,[rcx].SMALL_RECT.Bottom
    sub edx,eax
    inc edx
    mov rows,edx
    .ifs ( cols <= 0 || rows <= 0 )
        .return( 1 )
    .endif
    mov eax,dwBufferSize
    movzx edx,ax
    lea eax,[rdx*4]
    mov stride,rax
    mov eax,dwBufferCoord
    movzx ecx,ax
    shr eax,16
    imul eax,edx
    add eax,ecx
    lea rbx,[rbx+rax*4]
    GetConsoleCursorInfo(fp, &ci)
    fprintf(fp, ESC "7")
    .if ( ci.bVisible )
        fprintf(fp, CSI "?25l")
    .endif
    .for ( : rows > 0 : rows--, y++, rbx += stride )
        __conwrite_span(fp, rbx, x, y, cols)
    .endf
    fprintf(fp, ESC "8")
    .if ( ci.bVisible )
        fprintf(fp, CSI "?25h")
    .endif
    fflush(fp)
    .return( 1 )
    endp

    end
