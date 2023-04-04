; _RCCENTERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_rccenterA proc wc:TRECT, p:PCHAR_INFO, _rc:TRECT, attrib:WORD, string:LPSTR

   .new rc:TRECT = _rc
    xor eax,eax
    .while ( byte ptr [string+rax])
        inc eax
    .endw
    movzx r10d,rc.col
    movzx edx,rc.x
    .if ( eax > r10d )

        add string,rax
        sub string,r10
    .else
        sub r10d,eax
        shr r10d,1
        add edx,r10d
    .endif
    _rcputsA(wc, p, dl, rc.y, attrib, string)
    ret

_rccenterA endp

    end
