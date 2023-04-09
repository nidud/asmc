; CHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include linux/kernel.inc

    .code

chdir proc directory:string_t

    .ifsd ( sys_chdir(rdi) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
    ret

chdir endp

    end
