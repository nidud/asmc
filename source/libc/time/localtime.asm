; LOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

    .data
     tb tm <>

    .code

localtime proc ptime:ptr time_t
    .ifd _localtime_s( &tb, ldr(ptime) )
        _set_errno( eax )
        .return( 0 )
    .endif
    lea rax,tb
    ret
    endp

    end
