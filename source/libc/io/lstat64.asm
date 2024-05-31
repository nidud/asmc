; LSTAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include sys/stat.inc
ifdef __UNIX__
include sys/syscall.inc
endif

    .code

lstat64 proc file:string_t, buf:PSTAT64
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_newlstat(rdi, rsi) < 0 )
else
    .ifs ( sys_newlstat64(file, buf) < 0 )
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
lstat64 endp

    end
