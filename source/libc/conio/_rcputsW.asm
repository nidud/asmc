; _RCPUTSW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputsW proc uses rbx rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, string:LPWSTR

    .new retval:int_t = 0
    .new pos:TRECT = { x, y, 1, 1 }
    .for ( rbx = string : wchar_t ptr [rbx] : rbx += 2, pos.x++, retval++ )

        movzx ecx,wchar_t ptr [rbx]
        _rcputc(rc, pos, p, cx)
        .if ( attrib )
            _rcputa(rc, pos, p, attrib)
        .endif
    .endf
    .return( retval )

_rcputsW endp

    end
