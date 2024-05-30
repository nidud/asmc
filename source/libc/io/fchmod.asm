; FCHMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

fchmod proc fd:int_t, mode:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_fchmod(edi, esi) < 0 )
else
    .ifs ( sys_fchmod(fd, mode) < 0 )
endif
        neg eax
else
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret
fchmod endp

    end
