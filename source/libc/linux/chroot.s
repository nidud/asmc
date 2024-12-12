; CHROOT.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

chroot proc path:string_t

    .ifsd ( sys_chroot( ldr(path) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

chroot endp

    end
