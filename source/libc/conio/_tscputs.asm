; _TSCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputs proc uses rbx x:BYTE, y:BYTE, string:tstring_t

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : tchar_t ptr [rbx] : rbx+=tchar_t, x++, retval++ )

        movzx ecx,tchar_t ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scputs endp

    end
