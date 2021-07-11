; _SCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputw proc x:int_t, y:int_t, l:int_t, w:ushort_t

    shr r9d,8
    .ifnz
        _scputa(ecx, edx, r8d, r9b)
    .endif
    mov r9b,byte ptr w
    _scputc(x, y, l, r9b)
    ret

_scputw endp

    end
