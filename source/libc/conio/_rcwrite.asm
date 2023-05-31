; _RCWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rcx:PCONSOLE

_rcwrite proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

    ldr rsi,p

    _cbeginpaint()

    mov     rcx,_console
    movzx   eax,[rcx].rc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].buffer
    mov     rdi,rax
    movzx   ebx,word ptr rc[2]
    mov     dh,[rcx].rc.col
    add     dl,bl

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

        mov   rax,rdi
        movzx ecx,bl
        rep   movsd
        mov   cl,dh
        lea   rdi,[rax+rcx*4]
    .endf

    _cendpaint()

    .return( p )

_rcwrite endp

    end
