; _CHGSIGN.ASM--
; Copyright (C) 2017 Asmc Developers
;
include float.inc

.code

_chgsign proc x:REAL8

    xor byte ptr x[7],0x80
    fld x
    ret

_chgsign endp

    end
