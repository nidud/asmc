; FSETPOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

.code

fsetpos proc uses rbx stream:LPFILE, pos:ptr fpos_t

    ldr rcx,stream
    ldr rbx,pos

    .if ( rcx == NULL || rbx == NULL )
        .return( _set_errno( EINVAL ) )
    .endif
    _fseeki64(rcx, [rbx], SEEK_SET)
    ret

fsetpos endp

    end
