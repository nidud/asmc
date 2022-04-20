; _WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

.code

_write proc fd:int_t, buf:ptr, cnt:uint_t

    mov eax,cnt                 ; cnt
    .return .if !rax            ; nothing to do

    .if ( fd >= _NFILE_ )       ; validate handle
                                ; out of range -- return error
        _set_errno(EBADF)
        .return -1
    .endif
    .return( sys_write(fd, buf, cnt) )

_write endp

    end
