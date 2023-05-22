; _WTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_wtoi proc string:LPWSTR

    ldr rcx,string
    .return( _wtol( rcx ) )

_wtoi endp

    end
