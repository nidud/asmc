; _LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_lseek proc handle:SINT, offs:QWORD, pos:UINT

    .if r8d == SEEK_SET
        mov edx,edx
    .endif
    _lseeki64(ecx, rdx, r8d)
    ret

_lseek endp

    end
