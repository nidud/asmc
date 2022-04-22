; _LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

_lseek proc handle:SINT, offs:QWORD, pos:UINT

    .if ( edx == SEEK_SET )

        mov esi,esi
    .endif
    sys_lseek(edi, rsi, edx)
    ret

_lseek endp

    end
