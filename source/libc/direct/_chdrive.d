; _CHDRIVE.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include errno.inc
include sys/doscall.inc

    .code

_chdrive proc drive:int_t

    .if dos_chdrive( drive )
        _dosmaperr( dx )
    .endif
    ret

_chdrive endp

    end
