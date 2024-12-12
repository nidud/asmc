; FCHOWN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

fchown proc fd:int_t, user:uid_t, grp:gid_t

    .ifsd ( sys_fchown(ldr(fd), ldr(user), ldr(grp)) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

fchown endp

    end
