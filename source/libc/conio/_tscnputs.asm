; _TSCNPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scnputs proc uses rbx x:BYTE, y:BYTE, n:BYTE, string:LPTSTR

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : TCHAR ptr [rbx] && n : rbx+=TCHAR, n--, x++, retval++ )

        movzx ecx,TCHAR ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scnputs endp

    end
