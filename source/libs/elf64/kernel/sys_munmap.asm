; SYS_MUNMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include linux/kernel.inc

.code

sys_munmap proc adr:ptr, len:size_t

    .assert( adr )

    mov eax,SYS_MUNMAP
    syscall
    ret

sys_munmap endp

    end
