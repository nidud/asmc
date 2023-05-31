; TCGETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
include termios.inc
endif

    .code

ifdef __UNIX__
tcgetattr proc fd:int_t, termios_p:ptr termios

    .ifs ( edi < 0 )

        _set_errno(EBADF)
        .return( -1 )
    .endif
    .if ( rsi == NULL )

        _set_errno(EINVAL)
        .return( -1 )
    .endif
    .ifsd ( sys_ioctl(edi, TCGETS, rsi) < 0 )

        neg eax
        _set_errno(eax)
        mov rax,-1
    .endif
    ret

tcgetattr endp
endif
    end
