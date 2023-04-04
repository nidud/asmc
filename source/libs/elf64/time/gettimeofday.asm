; GETTIMEOFDAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include linux/kernel.inc

    .code

gettimeofday proc tv:ptr timeval, tz:ptr timezone

    .ifs ( sys_gettimeofday(tv, tz) < 0 )

        neg eax
        _set_errno(eax)
        .return( -1 )
    .endif
    .return( 0 )

gettimeofday endp

    end
