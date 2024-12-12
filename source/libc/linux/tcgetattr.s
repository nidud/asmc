; TCGETATTR.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include termios.inc
include sys/ioctl.inc
include sys/syscall.inc

    .code

tcgetattr proc fd:int_t, termios_p:ptr termios

    .if ( ldr(termios_p) == NULL )

        .return( _set_errno( EINVAL ) )
    .endif
    ioctl( ldr(fd), TCGETS, ldr(termios_p) )
    ret

tcgetattr endp

    end
