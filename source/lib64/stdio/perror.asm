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

perror proc frame message:string_t

    .if rcx
        .if byte ptr [rcx]

            _write(2, message, strlen(rcx))
            _write(2, ": ", 2)
        .endif
        mov message,_get_sys_err_msg(_get_errno(0))
        _write(2, message, strlen(rax))
        _write(2, "\n", 1)
    .endif
    ret

perror endp

    end
