; SELECT.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/select.inc
include sys/syscall.inc

.code

select proc nfds:int_t, readfds:ptr fd_set, writefds:ptr fd_set, exceptfds:ptr fd_set, timeout:ptr timeval

    .ifsd ( sys_select( ldr(nfds), ldr(readfds), ldr(writefds), ldr(exceptfds), ldr(timeout) ) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

select endp

    end
