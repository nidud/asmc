; _TSCCENTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc
include tchar.inc

    .code

_sccenter proc uses rbx x:BYTE, y:BYTE, lsize:BYTE, string:LPTSTR

    movzx ebx,lsize
    .ifd ( _tcslen( string ) > ebx )

ifdef _UNICODE
        add ebx,ebx
        add eax,eax
endif
        add string,rax
        sub string,rbx
    .else
        sub ebx,eax
        shr ebx,1
        add x,bl
    .endif
    _scputs( x, y, string )
    ret

_sccenter endp

    end
