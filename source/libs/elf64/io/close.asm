; CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

close proc fd:int_t

    .if ( fd < 3 || fd >= _NFILE_ )

        _set_errno(EBADF)
        .return(0)
    .endif
    lea rcx,_osfile
    mov byte ptr [rdi+rcx],0
    .return( sys_close(fd) )

close endp

    end
