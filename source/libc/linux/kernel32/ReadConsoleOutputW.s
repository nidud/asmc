; READCONSOLEOUTPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc

.code
 assume rcx:PCONSOLE
ifndef _WIN64
 assume uses esi edi
endif

ReadConsoleOutputW proc WINAPI uses rbx fp:HANDLE, lpBuffer:PCHAR_INFO,
        dwBufferSize:COORD, dwBufferCoord:COORD, lpReadRegion:PSMALL_RECT
   .new rc:TRECT
    ldr rsi,lpBuffer
    mov rdi,lpReadRegion
    mov ax,[rdi].SMALL_RECT.Top
    mov cx,[rdi].SMALL_RECT.Bottom
    mov rc.y,al
    sub cx,ax
    inc cx
    mov rc.row,cl
    mov ax,[rdi].SMALL_RECT.Left
    mov cx,[rdi].SMALL_RECT.Right
    mov rc.x,al
    sub cx,ax
    inc cx
    mov rc.col,cl
    mov rcx,_console
    movzx eax,[rcx].rc.col
    mul rc.y
    movzx edx,rc.x
    add eax,edx
    shl eax,2
    add rax,[rcx].buffer
    mov rdi,rsi
    mov rsi,rax
    movzx ebx,word ptr rc[2]
    mov dh,[rcx].rc.col
    add dl,bl
    .if ( dl > dh )
        mov bl,dh
        sub bl,rc.x
    .endif
    mov al,bh
    add al,rc.y
    .if ( al > [rcx].rc.row )
        mov al,[rcx].rc.row
        mov bh,al
        sub bh,rc.y
    .endif
    .for ( dl = 0 : dl < bh : dl++ )
        mov rax,rsi
        movzx ecx,bl
        rep movsd
        mov cl,dh
        lea rsi,[rax+rcx*4]
    .endf
    .return( 1 )
    endp

    end
