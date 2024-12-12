; PSELECT.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/select.inc
include sys/syscall.inc

.code

pselect proc nfds:int_t, readfds:ptr fd_set, writefds:ptr fd_set, exceptfds:ptr fd_set, timeout:ptr timespec, sigmask:ptr sigset_t

    .ifsd ( sys_pselect6( ldr(nfds), ldr(readfds), ldr(writefds), ldr(exceptfds), ldr(timeout), ldr(sigmask) ) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

pselect endp

    end
