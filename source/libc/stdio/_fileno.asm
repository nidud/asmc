; _FILENO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_fileno proc fp:LPFILE

ifndef _WIN64
    mov ecx,fp
endif
   .return( [rcx].FILE._file )

_fileno endp

    end
