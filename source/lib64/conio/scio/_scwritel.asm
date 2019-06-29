; _SCWRITEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scwritel proc x:int_t, y:int_t, l:int_t, p:PCHAR_INFO

  local rc:SMALL_RECT

    movzx eax,cl
    movzx edx,dl
    mov rc.Top,dx
    mov rc.Left,ax
    mov ecx,r8d
    .ifs ecx < 0
        not ecx
        mov r8d,ecx
        add edx,ecx
        dec edx
        shl ecx,16
        mov cx,1
    .else
        add eax,ecx
        add ecx,0x10000
    .endif
    mov rc.Right,ax
    mov rc.Bottom,dx
    mov rdx,r9
    WriteConsoleOutput(hStdOutput, rdx, ecx, 0, &rc)
    free(p)
    ret

_scwritel endp

    END
