; _TRCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputs proc uses rbx rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, string:LPTSTR

    .new retval:int_t = 0
    .new pos:TRECT = { x, y, 1, 1 }
    .for ( rbx = string : TCHAR ptr [rbx] : rbx+=TCHAR, pos.x++, retval++ )

        movzx ecx,TCHAR ptr [rbx]
        _rcputc(rc, pos, p, cx)
        .if ( attrib )
            _rcputa(rc, pos, p, attrib)
        .endif
    .endf
    .return( retval )

_rcputs endp

    end
