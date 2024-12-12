; BRK.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
include sys/syscall.inc

.code

brk proc p:ptr

    .ifsd ( sys_brk( ldr(p) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

brk endp

    end
