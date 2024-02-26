; _TPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
ifdef _UNICODE
include conio.inc
include wchar.inc
else
include io.inc
endif
include tchar.inc

    .code

_putts proc uses rbx string:LPTSTR

    ldr rbx,string
ifdef _UNICODE
    .new retval:int_t = 0
    .for ( : TCHAR ptr [rbx] : rbx+=TCHAR, retval++ )

        movzx ecx,TCHAR ptr [rbx]
        .if ( _puttch( ecx ) == WEOF )

           .return
        .endif
    .endf
    mov eax,retval
else
    _write( 1, string, strlen( string ) )
endif
    ret

_putts endp

    end
