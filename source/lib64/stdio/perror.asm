; PERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include cruntime.inc
include stdio.inc
include stdlib.inc
include string.inc
include syserr.inc
include mtdll.inc
include io.inc
include internal.inc

    .code

perror proc frame message:string_t

  local fh:int_t

    mov fh,2
    _lock_fh( fh )  ; acquire file handle lock

    mov rcx,message
    .if rcx

        .if byte ptr [rcx]

            _write_nolock(fh, message, strlen(rcx))
            _write_nolock(fh, ": ", 2)
        .endif

        mov ecx,_errno()
        mov message,_get_sys_err_msg(ecx)
        _write_nolock(fh, message, strlen(rax))
        _write_nolock(fh, "\n", 1)
    .endif
    _unlock_fh( fh ) ; release file handle lock
    ret

perror endp

    end
