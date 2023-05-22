; FEOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

feof proc stream:LPFILE

    ldr rcx,stream
    mov eax,[rcx]._iobuf._flag
    and eax,_IOEOF
    ret

feof endp

    end
