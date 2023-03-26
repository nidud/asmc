; _SCREADL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scgetl proc uses rbx x:int_t, y:int_t, l:int_t

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
        ReadConsoleOutputW( _confh, rbx, ecx, 0, &rc )
        mov rax,rbx
    .endif
    ret

_scgetl endp

_scputl proc x:int_t, y:int_t, l:int_t, p:PCHAR_INFO

  local rc:SMALL_RECT

    movzx eax,byte ptr x
    movzx edx,byte ptr y

    mov rc.Top,dx
    mov rc.Left,ax

    mov ecx,l
    .ifs ( ecx < 0)

        not ecx
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

    WriteConsoleOutputW( _confh, p, ecx, 0, &rc )
    free( p )
    ret

_scputl endp

    end
