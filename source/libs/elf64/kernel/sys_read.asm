; SYS_READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include linux/kernel.inc

.code

sys_read proc fd:int_t, buf:ptr, count:size_t

    mov eax,SYS_READ
    syscall
    ret

sys_read endp

    end
