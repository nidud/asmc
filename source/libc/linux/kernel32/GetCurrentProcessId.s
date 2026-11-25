; GETCURRENTPROCESSID.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include unistd.inc
include sys/syscall.inc
include processthreadsapi.inc

.code

 GetCurrentProcessId proc WINAPI
    sys_getpid()
    ret
    endp

    end
