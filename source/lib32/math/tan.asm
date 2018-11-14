; TAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

tan proc x:double

  local q:dword

    fld x
    fptan
    fstp q
    ret

tan endp

    end
