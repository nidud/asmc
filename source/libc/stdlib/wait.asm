; _WAIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include sys/wait.inc
include errno.inc

.code

_wait proc wstatus:ptr int_t

    waitpid(-1, wstatus, 0)
    ret

_wait endp

    end
