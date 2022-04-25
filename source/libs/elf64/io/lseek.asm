; LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

lseek proc fd:int_t, offs:uint64_t, pos:uint_t

    .ifs ( sys_lseek(fd, offs, pos) < 0 )

        neg eax
        _set_errno(eax)
        mov rax,-1
    .endif
    ret

lseek endp

    end
