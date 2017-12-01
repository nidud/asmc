; _QFISNAN.ASM--
; Copyright (C) 2017 Asmc Developers
;
.code

IsNaNq::

    xor eax,eax
    .repeat

        movzx r10d,word ptr [rcx+14]
        .break .if r10d != 0x7FFF

        inc eax
        mov r10,[rcx]
        or  r10,[rcx+6]
        .break .ifnz

        dec eax
    .until 1
    ret

    end
