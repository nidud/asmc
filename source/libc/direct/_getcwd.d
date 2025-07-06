; _GETCWD.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include errno.inc
include sys/doscall.inc

    .code

_getcwd proc directory:string_t, maxlen:int_t

    .if dos_getcwd( directory )
        _dosmaperr( cx )
        xor ax,ax
        cwd
    .endif
    ret

_getcwd endp

    end
