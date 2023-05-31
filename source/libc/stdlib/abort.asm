; ABORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include setjmp.inc

    .data
    jmp_exit _JUMP_BUFFER <>

    .code

abort proc

    longjmp(&jmp_exit, 1)
    ret

abort endp

Install proc private

    .if _setjmp(&jmp_exit)

        exit(eax)
    .endif
    ret

Install endp

.pragma init(Install, 1)

    end
