; _RCBPRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcbprc proc w:TRECT, rc:TRECT, p:PCHAR_INFO

    ldr     eax,w
    ldr     rcx,p
    ldr     edx,rc

    shr     eax,16
    mul     dh
    movzx   edx,dl
    add     eax,edx
    shl     eax,2
    add     rax,rcx
    ret

_rcbprc endp

    end
