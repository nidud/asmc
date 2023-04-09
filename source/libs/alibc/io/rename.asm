; RENAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

rename proc old:string_t, new:string_t

    .if ( !rdi || !rsi )

        _set_errno(EINVAL)
        .return( -1 )
    .endif
    .ifs ( sys_rename(rdi, rsi) < 0 )

        neg eax
        _set_errno(eax)
        .return( -1 )
    .endif
    .return( 0 )

rename endp

    end
