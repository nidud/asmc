; _SCCENTERW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_sccenterW proc uses rbx x:BYTE, y:BYTE, lsize:BYTE, string:LPWSTR

    movzx ebx,lsize
    .ifd ( wcslen( string ) > ebx )

        add ebx,ebx
        add eax,eax
        add string,rax
        sub string,rbx
    .else
        sub ebx,eax
        shr ebx,1
        add x,bl
    .endif
    _scputsW( x, y, string )
    ret

_sccenterW endp

    end
