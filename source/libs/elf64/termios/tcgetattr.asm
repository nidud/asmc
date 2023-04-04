; TCGETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include linux/kernel.inc
include termios.inc

    .code

tcgetattr proc fd:int_t, termios_p:ptr termios

    .ifs ( fd < 0 )

        _set_errno(EBADF)
        .return -1
    .endif
    .if ( termios_p == NULL )

        _set_errno(EINVAL)
        .return -1
    .endif
    .ifsd ( sys_ioctl(fd, TCGETS, termios_p) < 0 )

        neg eax
        _set_errno(eax)
        .return -1
    .endif
    ret

tcgetattr endp

    end
