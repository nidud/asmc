; _TCSLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc
include tchar.inc

    .code

_tcslwr proc uses rbx string:tstring_t

    ldr rbx,string
    .for ( : tchar_t ptr [rbx] : rbx+=tchar_t )

        movzx ecx,tchar_t ptr [rbx]
        _totlower(ecx)
        mov [rbx],_tal
    .endf
    .return( string )

_tcslwr endp

    end
