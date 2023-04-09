; TIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include linux/kernel.inc

    .code

time proc timeptr:ptr time_t

    .return( sys_time(rdi) )

time endp

    end
