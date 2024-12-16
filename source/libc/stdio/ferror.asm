; FERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

    .code

ferror proc stream:LPFILE

    ldr rcx,stream

    .if ( rcx == NULL )

        _set_errno(EINVAL)
        .return( 0 )
    .endif
    mov eax,[rcx]._iobuf._flag
    and eax,_IOERR
    ret

ferror endp

    end
