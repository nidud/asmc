; _RCBPRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcbprc proc w:TRECT, rc:TRECT, p:PCHAR_INFO

    movzx   eax,w.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,p
    ret

_rcbprc endp

    end
