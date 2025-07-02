; _TSCNPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scnputs proc uses rbx x:BYTE, y:BYTE, n:BYTE, string:tstring_t

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : tchar_t ptr [rbx] && n : rbx+=tchar_t, n--, x++, retval++ )

        movzx ecx,tchar_t ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scnputs endp

    end
