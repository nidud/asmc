; QUADISINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

quadisinf::

    xor eax,eax
    .repeat

        mov r10,[rcx]
        or  r10,[rcx+6]
        .break .ifnz

        movzx r10d,word ptr [rcx+14]
        and r10d,0x7FFF
        .break .if r10d != 0x7FFF

        inc eax
    .until 1
    ret

    end
