; PERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc
include syserr.inc
include io.inc

    .code

perror proc uses rbx message:string_t

    mov rbx,message
    .if rbx
        .if byte ptr [rbx]

            _write(2, rbx, strlen(rbx))
            _write(2, ": ", 2)
        .endif
        mov rbx,_get_sys_err_msg(_get_errno(0))
        _write(2, rbx, strlen(rbx))
        _write(2, "\n", 1)
    .endif
    ret

perror endp

    end
