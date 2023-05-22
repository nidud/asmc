; _SCCENTERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_sccenterA proc uses rbx x:BYTE, y:BYTE, lsize:BYTE, string:LPSTR

    movzx ebx,lsize
    .ifd ( strlen( string ) > ebx )

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
