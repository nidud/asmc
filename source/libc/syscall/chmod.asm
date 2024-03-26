; CHMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include fcntl.inc
ifdef __UNIX__
include sys/stat.inc
include sys/syscall.inc
endif

.code

chmod proc path:string_t, mode:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_chmod(rdi, esi) < 0 )
else
    .ifs ( sys_chmod(path, mode) < 0 )
endif
        neg eax
        _set_errno( eax )
    .endif
else
    int 3
endif
    ret

chmod endp

    end
