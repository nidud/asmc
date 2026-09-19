; COS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

ifndef _WIN64
cos proc x:double
    fld x
    fcos
    ret
    endp
endif
    end
