; _CLEARFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_clearfp proc

    fnclex
    ret

_clearfp endp

    end
