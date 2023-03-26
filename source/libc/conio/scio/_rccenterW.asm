; _RCCENTERW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_rccenterW proc wc:TRECT, p:PCHAR_INFO, rc:TRECT, attrib:WORD, string:LPWSTR

    wcslen( string )
    movzx ecx,rc.col
    movzx edx,rc.x
    .if ( eax > ecx )

        add eax,eax
        add ecx,ecx
        add string,rax
        sub string,rcx
    .else
        sub ecx,eax
        shr ecx,1
        add edx,ecx
    .endif
    movzx ecx,rc.y
    _rcputsW(wc, p, edx, ecx, attrib, string)
    ret

_rccenterW endp

    end
