; TCGETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
include termios.inc
endif

    .code

ifdef __UNIX__
tcgetattr proc fd:int_t, termios_p:ptr termios

    .ifs ( edi < 0 )

        .return( _set_errno( EBADF ) )
    .endif
    .if ( rsi == NULL )

        .return( _set_errno( EINVAL ) )
    .endif
    .ifsd ( sys_ioctl(edi, TCGETS, rsi) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

tcgetattr endp
endif
    end
