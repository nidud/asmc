; _RCGETW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcgetw proc rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE

    movzx   eax,rc.col
    mul     y
    movzx   edx,x
    add     edx,eax
    shl     edx,2
    add     rdx,p
    mov     eax,[rdx]
    ret

_rcgetw endp

    end
