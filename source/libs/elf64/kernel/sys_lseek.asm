; SYS_LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include linux/kernel.inc

.code

sys_lseek proc fd:int_t, off:size_t, whence:uint_t

    mov eax,SYS_LSEEK
    syscall
    ret

sys_lseek endp

    end
