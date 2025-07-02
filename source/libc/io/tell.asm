; TELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_tell proc handle:int_t

    _lseek( ldr(handle), 0, SEEK_CUR )
    ret

_tell endp

    end
