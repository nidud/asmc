; _TRCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputs proc uses rbx rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, string:tstring_t

    .new retval:int_t = 0
    .new pos:TRECT = { x, y, 1, 1 }
    .for ( rbx = string : tchar_t ptr [rbx] : rbx+=tchar_t, pos.x++, retval++ )

        movzx ecx,tchar_t ptr [rbx]
        _rcputc(rc, pos, p, cx)
        .if ( attrib )
            _rcputa(rc, pos, p, attrib)
        .endif
    .endf
    .return( retval )

_rcputs endp

    end
