; _WTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_wtoi proc string:LPWSTR

ifdef _WIN64
    .return( _wtol( rcx ) )
else
    .return( _wtol( string ) )
endif

_wtoi endp

    end
