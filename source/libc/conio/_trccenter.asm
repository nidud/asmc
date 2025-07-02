; _TRCCENTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc
include tchar.inc

    .code

_rccenter proc wc:TRECT, p:PCHAR_INFO, rc:TRECT, attrib:WORD, string:tstring_t

    _tcslen( string )
    movzx ecx,rc.col
    movzx edx,rc.x
    .if ( eax > ecx )

ifdef _UNICODE
        add eax,eax
        add ecx,ecx
endif
        add string,rax
        sub string,rcx
    .else
        sub ecx,eax
        shr ecx,1
        add edx,ecx
    .endif
    _rcputs(wc, p, dl, rc.y, attrib, string)
    ret

_rccenter endp

    end
