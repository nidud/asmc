; _TSCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputs proc uses rbx x:BYTE, y:BYTE, string:LPTSTR

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : TCHAR ptr [rbx] : rbx+=TCHAR, x++, retval++ )

        movzx ecx,TCHAR ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scputs endp

    end
