; _RCGETW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcgetw proc rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE

    mov     eax,edi
    shr     eax,16
    movzx   eax,al
    mul     cl
    movzx   edx,dl
    add     edx,eax
    shl     edx,2
    add     rdx,rsi
    mov     eax,[rdx]
    ret

_rcgetw endp

    end
