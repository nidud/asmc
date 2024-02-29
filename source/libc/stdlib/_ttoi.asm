; _TTOI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ttoi proc string:LPTSTR

    ldr rcx,string

   .return( _ttol( rcx ) )

_ttoi endp

    end
