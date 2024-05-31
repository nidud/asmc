; POLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/poll.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

poll proc fds:ptr pollfd, nfds:nfds_t, timeout:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_poll(rdi, esi, edx) < 0 )
else
    .ifs ( sys_poll(fds, nfds, timeout) < 0 )
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
poll endp

    end
