; _WRITECONSOLEOUTPUTW.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include io.inc
include conio.inc
include consoleapi.inc

.code

_writeconsoleoutputw proc WINAPI uses rdi rbx hConsoleOutput:HANDLE, lpBuffer:PCHAR_INFO,
        dwBufferSize:COORD, dwBufferCoord:COORD, lpWriteRegion:PSMALL_RECT

   .new b[2048]:byte
   .new p:int_t
   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new cols:int_t
   .new wc:int_t
   .new color_changed:int_t = 0
   .new foreground:int_t = 0
   .new background:int_t = 0

    ldr rbx,lpBuffer
    ldr rcx,lpWriteRegion

    movzx   eax,[rcx].SMALL_RECT.Left
    inc     eax
    mov     x,eax
    movzx   eax,[rcx].SMALL_RECT.Top
    inc     eax
    mov     y,eax
    mov     ax,[rcx].SMALL_RECT.Right
    sub     ax,[rcx].SMALL_RECT.Left
    inc     eax
    mov     cols,eax

    mov p,sprintf(&b, CSI "%d;%dH", y, x)

    .for ( l = cols : l : l--, rbx += 4 )

        movzx   eax,byte ptr [rbx+2]
        mov     ecx,eax
        and     eax,0x0F
        shr     ecx,4

        .if ( eax != foreground || ecx != background )

            mov color_changed,1
            mov foreground,eax
            mov background,ecx

            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]
            mov edi,p
            add p,sprintf(&b[rdi], CSI "38;5;%dm\e[48;5;%dm", eax, ecx)
        .endif
        _wtoutf([rbx])
        .for ( edi = p : ecx : ecx--, edi++ )
            mov b[rdi],al
            shr eax,8
        .endf
        mov p,edi
    .endf
    .if ( color_changed )
        mov ecx,p
        mov b[rcx],0x1B
        mov b[rcx+1],'['
        mov b[rcx+2],'m'
        add p,3
    .endif
    _write(_confd, &b, p)
    mov eax,1
    ret

_writeconsoleoutputw endp

    end
