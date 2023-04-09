; RMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include linux/kernel.inc

    .code

rmdir proc directory:string_t

    .ifsd ( sys_rmdir(rdi) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
    ret

rmdir endp

    end
