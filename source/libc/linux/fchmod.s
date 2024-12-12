; FCHMOD.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include sys/syscall.inc

.code

fchmod proc fd:int_t, mode:int_t

    .ifsd ( sys_fchmod(ldr(fd), ldr(mode)) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

fchmod endp

    end
