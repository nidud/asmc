; IOCTL.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/ioctl.inc
include sys/syscall.inc

.code

ioctl proc fd:int_t, cmd:int_t, argp:ptr

    ldr eax,fd

    .ifs ( eax < 0 )

        .return( _set_errno( EBADF ) )
    .endif
    .ifsd ( sys_ioctl( eax, ldr(cmd), ldr(argp) ) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

ioctl endp

    end
