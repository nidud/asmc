; _CHDIR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include errno.inc
include sys/doscall.inc

    .code

_chdir proc directory:string_t

    .if dos_chdir( directory )
        _dosmaperr( dx )
    .endif
    ret

_chdir endp

    end
