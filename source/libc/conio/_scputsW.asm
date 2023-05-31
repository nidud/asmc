; _SCPUTSW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputsW proc uses rbx x:BYTE, y:BYTE, string:LPWSTR

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : wchar_t ptr [rbx] : rbx += 2, x++, retval++ )

        movzx ecx,wchar_t ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scputsW endp

    end
