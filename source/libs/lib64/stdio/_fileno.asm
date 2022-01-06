; _FILENO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_fileno proc fp:LPFILE

    mov eax,[rcx].FILE._file
    ret

_fileno endp

    end
