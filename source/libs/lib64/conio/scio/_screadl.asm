; _SCREADL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_screadl proc uses rbx x:int_t, y:int_t, l:int_t

  local rc:SMALL_RECT

    movzx eax,cl
    movzx edx,dl
    mov rc.Left,ax
    mov rc.Top,dx
    mov ebx,r8d

    .ifs ebx < 0
        not ebx
        mov r8d,ebx
        add edx,ebx
        dec edx
        shl ebx,16
        mov bx,1
    .else
        add eax,ebx
        add ebx,0x10000
    .endif

    mov rc.Right,ax
    mov rc.Bottom,dx
    shl r8d,2

    .if malloc(r8d)

        mov r8d,ebx
        mov rbx,rax
        ReadConsoleOutput(hStdOutput, rbx, r8d, 0, &rc)
        mov rax,rbx
    .endif
    ret

_screadl endp

    END
