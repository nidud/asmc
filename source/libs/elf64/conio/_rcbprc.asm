; _RCBPRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcbprc proc w:TRECT, rc:TRECT, p:PCHAR_INFO

    mov     ecx,esi
    shr     edi,16
    and     edi,0xFF
    mov     eax,edi
    mul     ch
    movzx   edx,cl
    add     eax,edx
    shl     eax,2
    add     rax,p
    ret

_rcbprc endp

    end
