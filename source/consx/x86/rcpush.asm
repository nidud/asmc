; RCPUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcpush proc lines:UINT

    mov eax,_scrcol
    mov ah,byte ptr lines
    shl eax,16
    rcopen(eax, 0, 0, 0, 0)
    ret

rcpush endp

    END
