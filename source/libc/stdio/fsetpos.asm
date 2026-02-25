; FSETPOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

.code

fsetpos proc stream:LPFILE, pos:ptr fpos_t
    ldr rcx,stream
    ldr rdx,pos
    .if ( rcx == NULL || rdx == NULL )
        .return( _set_errno( EINVAL ) )
    .endif
    _fseeki64(rcx, [rdx], SEEK_SET)
    ret
    endp

    end
