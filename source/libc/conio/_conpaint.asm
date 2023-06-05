; _CONPAINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdlib.inc

.code

_writeline proc private uses rbx x:BYTE, y:BYTE, l:BYTE, p:PCHAR_INFO

ifdef __UNIX__

   .new c:int_t
   .new a:int_t = 0
   .new f:byte = 0
   .new b:byte = 0

    mov rbx,p

    inc x ; zero based..
    inc y

    _cout(CSI "%d;%dH", y, x)

    .for ( : l : l--, rbx+=4 )

        movzx eax,byte ptr [rbx+2]
        mov ecx,eax
        and eax,0x0F
        shr ecx,4

        .if ( al != f || cl != b )

            mov a,1
            mov f,al
            mov b,cl

            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]

            _cout(CSI "38;5;%dm\e[48;5;%dm", eax, ecx)
        .endif
        mov c,_wtoutf([rbx])
        _write(_confd, &c, ecx)
    .endf
    .if ( a )
        _cout(CSI "m")
    .endif

else

   .new rc:SMALL_RECT
    movzx eax,x
    movzx edx,y
    mov rc.Top,dx
    mov rc.Left,ax
    movzx ecx,l
    add eax,ecx
    add ecx,0x10000
    mov rc.Right,ax
    mov rc.Bottom,dx
    WriteConsoleOutputW(_confh, p, ecx, 0, &rc)

endif
    ret

_writeline endp


_conpaint proc uses rbx

   .new rc:TRECT
   .new x:byte
   .new y:byte
   .new c:byte
   .new k:byte

ifdef __UNIX__
    _cout("\e7\e[?25l")
endif
    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc
    mov rbx,[rcx].TCONSOLE.window

    .for ( y = 0 : y < rc.row : y++ )

        .for ( c = 0, x = 0 : x < rc.col : x++, rbx+=4 )

            mov rdx,rbx
            mov rax,_console
            sub rdx,[rax].TCONSOLE.window
            add rdx,[rax].TCONSOLE.buffer
            mov eax,[rdx]

            .if ( eax != [rbx] )

                mov   [rbx],eax
                cmp   c,0
                cmovz rcx,rdx
                inc   c

            .elseif ( c )

                mov al,x
                sub al,c
                mov k,al
                _writeline(k, y, c, rcx)
                mov c,0
            .endif
        .endf
        .if ( c )

            mov al,x
            sub al,c
            mov k,al
            _writeline(k, y, c, rcx)
            mov c,0
        .endif
    .endf
ifdef __UNIX__
    _cout("\e8")
    .if ( _cursor.visible )
        _cout("\e[?25h")
    .endif
endif
    ret

_conpaint endp

    end
