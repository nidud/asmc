; FEOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

feof proc stream:LPFILE

    mov eax,[rdi]._iobuf._flag
    and rax,_IOEOF
    ret

feof endp

    END
