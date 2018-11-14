; _TELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

    option win64:rsp nosave

_tell proc handle:SINT

    _lseek(ecx, 0, SEEK_CUR)
    ret

_tell endp

    end
