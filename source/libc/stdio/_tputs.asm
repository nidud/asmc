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

_putts proc uses rbx string:tstring_t

   .new retval:int_t = 0

    ldr rbx,string
ifdef _UNICODE
    .for ( : tchar_t ptr [rbx] : rbx+=tchar_t, retval++ )

        movzx ecx,tchar_t ptr [rbx]
        .if ( _puttch( ecx ) == WEOF )

           .return
        .endif
    .endf
    mov ebx,retval
    _puttch( 10 )
    inc ebx
else
    _write( 1, rbx, strlen( rbx ) )
    mov ebx,eax
    mov retval,10
    _write( 1, &retval, 1 )
    add ebx,eax
endif
    mov eax,ebx
    ret

_putts endp

    end
