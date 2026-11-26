; EXITPROCESS.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc
include sys/syscall.inc

.code

 ExitProcess proc WINAPI retval:UINT
    sys_exit(ldr(retval))
    ret
    endp

    end
