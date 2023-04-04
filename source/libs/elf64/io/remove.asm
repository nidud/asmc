; REMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

.code

remove proc path:string_t

    .if ( !path )

        _set_errno(EINVAL)
        .return( -1 )
    .endif
    .ifs ( sys_unlink(path) < 0 )

        neg eax
        _set_errno(eax)
        .return( -1 )
    .endif
    .return( 0 )

remove endp

    end
