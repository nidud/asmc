; _SCGETP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rcx:PCONSOLE

_scgetp proc x:BYTE, y:BYTE, l:BYTE

    _cbeginpaint()

    mov     rcx,rax
    movzx   eax,[rcx].rc.col
    mul     y
    movzx   edx,x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].buffer
    mov     dl,l
    mov     dh,[rcx].rc.col
    mov     rcx,rax
    mov     al,x
    add     al,dl

    .if ( al > dh )

        mov dl,dh
        sub dl,x
    .endif
    ret

_scgetp endp

    end
