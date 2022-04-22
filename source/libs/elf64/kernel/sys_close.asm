; SYS_CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include linux/kernel.inc

.code

sys_close proc handle:int_t

    mov eax,SYS_CLOSE
    syscall
    ret

sys_close endp

    end
