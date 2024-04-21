; _RCADDRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_rcaddrc proc rc:TRECT, r2:TRECT

    ldr ecx,rc
    ldr eax,r2
    add ax,cx
    ret

_rcaddrc endp

    end
