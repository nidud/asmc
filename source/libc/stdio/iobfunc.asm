; IOBFUNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

__iob_func proc

    mov rax,stdin
    ret

__iob_func endp

    end
