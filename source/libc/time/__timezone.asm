; __TIMEZONE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

.code

__timezone proc

    lea rax,_timezone
    ret

__timezone endp

    end
