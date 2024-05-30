; VFORK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
endif
include errno.inc

.code

vfork proc
ifdef __UNIX__
    .ifs ( sys_vfork() < 0 )
        neg eax
else
        mov eax,ENOSYS
endif

        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

vfork endp

    end
