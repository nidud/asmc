; _RCBPRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcbprc proc w:TRECT, rc:TRECT, p:PCHAR_INFO

    mov     eax,edi
    shr     eax,16
    movzx   eax,al
    mov     ecx,esi
    mul     ch
    movzx   ecx,cl
    add     eax,ecx
    shl     eax,2
    add     rax,rdx
    ret

_rcbprc endp

    end
