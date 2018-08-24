include stdlib.inc
include crtl.inc
include setjmp.inc

    .data
    jmp_exit S_JMPBUF <>

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

.pragma(init(Install, 1))

    END
