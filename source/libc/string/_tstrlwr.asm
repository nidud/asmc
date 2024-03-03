; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc
include tchar.inc

    .code

_tcslwr proc uses rbx string:LPTSTR

    ldr rbx,string
    .for ( : TCHAR ptr [rbx] : rbx+=TCHAR )

        movzx ecx,TCHAR ptr [rbx]
        _totlower(ecx)
        mov [rbx],_tal
    .endf
    .return( string )

_tcslwr endp

    end
