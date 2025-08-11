; _GETPID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include process.inc
include errno.inc
ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
else
include processthreadsapi.inc
endif
ifndef __UNIX__
undef getpid
ALIAS <getpid>=<_getpid>
endif

.code

_getpid proc
ifdef __UNIX__
    .ifsd ( sys_getpid() < 0 )

        neg eax
        _set_errno( eax )
    .endif
else
    GetCurrentProcessId()
endif
    ret

_getpid endp

    end
