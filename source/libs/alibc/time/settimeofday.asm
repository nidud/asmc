; SETTIMEOFDAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include linux/kernel.inc

    .code

settimeofday proc tv:ptr timeval, tz:ptr timezone

    .ifs ( sys_settimeofday(rdi, rsi) < 0 )

        neg eax
        _set_errno(eax)
        .return( -1 )
    .endif
    .return( 0 )

settimeofday endp

    end
