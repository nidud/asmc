; _RMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include errno.inc
include sys/doscall.inc

    .code

_rmdir proc directory:string_t

    .if dos_rmdir( directory )
        _dosmaperr( dx )
    .endif
    ret

_rmdir endp

    end
