; CHOWN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

chown proc file:string_t, user:uid_t, grp:gid_t

    .ifsd ( sys_chown( ldr(file), ldr(user), ldr(grp) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

chown endp

    end
