; CHOWN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

chown proc file:string_t, user:uid_t, grp:gid_t
ifdef __UNIX__
    .ifs ( sys_chown( ldr(file), ldr(user), ldr(grp) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

chown endp

    end
