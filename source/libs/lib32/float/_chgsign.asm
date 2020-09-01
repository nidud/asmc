; _CHGSIGN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_chgsign proc x:REAL8

    xor byte ptr x[7],0x80
    fld x
    ret

_chgsign endp

    end
