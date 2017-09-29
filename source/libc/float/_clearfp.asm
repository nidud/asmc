; _CLEARFP.ASM--
; Copyright (C) 2017 Asmc Developers
;
include float.inc

.code

_clearfp proc

    fnclex
    ret

_clearfp endp

    end
