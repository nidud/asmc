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

lstat proc file:string_t, buf:PSTAT
ifdef __UNIX__
    .ifsd ( sys_newlstat( ldr(file), ldr(buf) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

lstat endp

    end
