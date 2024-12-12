; POLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/poll.inc
include errno.inc
include sys/syscall.inc

.code

poll proc fds:ptr pollfd, nfds:nfds_t, timeout:int_t

    .ifsd ( sys_poll( ldr(fds), ldr(nfds), ldr(timeout) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

poll endp

    end
