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

__initabort proc private

    .ifd _setjmp(&jmp_exit)

        exit(eax)
    .endif
    ret

__initabort endp

.pragma init(__initabort, 1)

    end
