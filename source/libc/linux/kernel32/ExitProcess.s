; EXITPROCESS.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc

.code

ExitProcess proc WINAPI retval:UINT
    exit(ldr(retval))
    ret
    endp

    end
