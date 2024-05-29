; __TZNAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

.code

__tzname proc

    lea rax,_tzname
    ret

__tzname endp

    end
