; _SCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputw proc x:int_t, y:int_t, l:int_t, w:ushort_t

    movzx ecx,w
    shr ecx,8
    .ifnz
        _scputa( x, y, l, cl )
    .endif
    movzx ecx,byte ptr w
    _scputc( x, y, l, cl )
    ret

_scputw endp

    end
