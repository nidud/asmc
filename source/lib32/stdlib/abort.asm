; ABORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include setjmp.inc

    .data
    jmp_exit JMPBUF <>

    .code

abort proc

    longjmp(&jmp_exit, 1)
    ret

abort endp

Install:
    .if _setjmp(&jmp_exit)

        exit(eax)
    .endif
    ret

.pragma init(Install, 1)

    END
