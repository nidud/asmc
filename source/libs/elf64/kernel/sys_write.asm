; SYS_WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include linux/kernel.inc

.code

sys_write proc fd:int_t, buf:ptr, count:size_t

    mov eax,SYS_WRITE
    syscall
    ret

sys_write endp

    end
