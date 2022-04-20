; SYS_EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include linux/kernel.inc

.code

sys_exit proc retval:int_t

    mov eax,60
    syscall
    ret

sys_exit endp

    end
