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

    movzx eax,byte ptr x
    movzx edx,byte ptr y

    mov rc.Left,ax
    mov rc.Top,dx

    mov ebx,l
    mov ecx,ebx

    .ifs ( ebx < 0 )

        not ebx
        mov ecx,ebx
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
    shl ecx,2

    .if malloc( ecx )

        mov ecx,ebx
        mov rbx,rax
        ReadConsoleOutput( _coninpfh, rbx, ecx, 0, &rc )
        mov rax,rbx
    .endif
    ret

_screadl endp

    end
