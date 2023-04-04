; _RCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputsA proc uses rbx r12 r13 _rc:TRECT, p:PCHAR_INFO, _x:BYTE, _y:BYTE, _at:WORD, string:LPSTR

    .new rc:TRECT    = _rc
    .new attrib:WORD = _at
    .new pos:TRECT   = { dl, cl, 1, 1 }

    .for ( r13=p, ebx=0, r12=string : char_t ptr [r12] : r12++, pos.x++, ebx++ )

        _rcputc(rc, pos, r13, [r12])
        .if ( attrib )
            _rcputa(rc, pos, r13, attrib)
        .endif
    .endf
    .return( ebx )

_rcputsA endp

    end
