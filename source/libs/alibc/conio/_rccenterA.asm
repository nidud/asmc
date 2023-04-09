; _RCCENTERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_rccenterA proc wc:TRECT, p:PCHAR_INFO, rc:TRECT, attrib:WORD, string:LPSTR

    xor eax,eax
    .while ( byte ptr [r8+rax])
        inc eax
    .endw
    movzx r10d,rc.col
    movzx edx,rc.x
    .if ( eax > r10d )

        add r8,rax
        sub r8,r10
    .else
        sub r10d,eax
        shr r10d,1
        add edx,r10d
    .endif
    _rcputsA(edi, rsi, dl, rc.y, cx, r8)
    ret

_rccenterA endp

    end
