; SYSCALL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include libc.inc
include linux/kernel.inc

    .code

main proc

    sys_write(1, "Hello world!\n", sizeof(@CStr(-0))-1 )
    sys_exit(0)

main endp

    end
