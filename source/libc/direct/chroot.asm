; CHROOT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
endif

.code

chroot proc path:string_t
ifdef __UNIX__
    .ifsd ( sys_chroot( ldr(path) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret
chroot endp

    end
