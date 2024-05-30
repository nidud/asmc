; ALARM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

alarm proc seconds:uint_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_alarm(edi) < 0 )
else
    .ifs ( sys_alarm(seconds) < 0 )
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
alarm endp

    end
