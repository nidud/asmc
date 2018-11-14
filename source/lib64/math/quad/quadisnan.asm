; QUADISNAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

quadisnan::

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
