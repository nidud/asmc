; _SCCENTERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_sccenterA proc uses rbx x:BYTE, y:BYTE, lsize:BYTE, string:LPSTR

    xor eax,eax
    .while ( byte ptr [string+rax])
        inc eax
    .endw
    movzx ebx,lsize
    .ifd ( eax > ebx )

        add string,rax
        sub string,rbx
    .else

        sub ebx,eax
        shr ebx,1
        add x,bl
    .endif
    _scputsA( x, y, string )
    ret

_sccenterA endp

    end
