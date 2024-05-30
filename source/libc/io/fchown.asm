; FCHOWN.ASM--
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

fchown proc fd:int_t, user:uid_t, grp:gid_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_fchown(edi, esi, edx) < 0 )
else
    .ifs ( sys_fchown(fd, user, grp) < 0 )
endif
        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret
fchown endp

    end
