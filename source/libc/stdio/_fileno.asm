; _FILENO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

    .code

_fileno proc fp:LPFILE

    ldr rcx,fp

    .if ( rcx == NULL )
        _set_errno(EINVAL)
    .else
        mov eax,[rcx].FILE._file
    .endif
    ret

_fileno endp

    end
