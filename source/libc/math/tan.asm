; TAN.ASM--
; Copyright (C) 2017 Asmc Developers
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
