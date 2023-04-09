; READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

read proc fh:int_t, buf:ptr, cnt:size_t

    xor eax,eax
    .return .if !edx            ; nothing to read
    .if ( edi >= _NFILE_ )       ; validate handle
                                ; out of range -- return error
        _set_errno(EBADF)
        .return -1
    .endif
    .return( sys_read(edi, rsi, edx) )

read endp

    end
