; WRITECONSOLEOUTPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include conio.inc

.code

WriteConsoleOutputW proc WINAPI uses rbx fp:HANDLE, lpBuffer:PCHAR_INFO,
        dwBufferSize:COORD, dwBufferCoord:COORD, lpWriteRegion:PSMALL_RECT

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

    movzx eax,[rcx].SMALL_RECT.Left
    inc eax
    mov x,eax
    movzx eax,[rcx].SMALL_RECT.Top
    inc eax
    mov y,eax
    mov ax,[rcx].SMALL_RECT.Right
    sub ax,[rcx].SMALL_RECT.Left
    inc eax
    mov cols,eax
    fprintf(fp, CSI "%d;%dH", y, x)
    .for ( l = cols : l : l--, rbx += 4 )
        movzx eax,byte ptr [rbx+2]
        mov ecx,eax
        and eax,0x0F
        shr ecx,4
        .if ( eax != foreground || ecx != background )
            mov color_changed,1
            mov foreground,eax
            mov background,ecx
            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]
            fprintf(fp, CSI "38;5;%dm" CSI "48;5;%dm", eax, ecx)
        .endif
        mov wc,_wtoutf([rbx])
        mov edx,ecx
        fwrite(&wc, 1, edx, fp)
    .endf
    .if ( color_changed )
        fprintf(fp, CSI "m")
    .endif
    mov eax,1
    ret
    endp

    end
