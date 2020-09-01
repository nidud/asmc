; _STATUSFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_statusfp proc __cdecl

  local cw:word

    fstcw cw
    movzx ecx,cw
    xor eax,eax

    .if ecx & 0x1
        or eax,_SW_INVALID
    .endif
    .if ecx & 0x2
        or eax,_SW_DENORMAL
    .endif
    .if ecx & 0x4
        or eax,_SW_ZERODIVIDE
    .endif
    .if ecx & 0x8
        or eax,_SW_OVERFLOW
    .endif
    .if ecx & 0x10
        or eax,_SW_UNDERFLOW
    .endif
    .if ecx & 0x20
        or eax,_SW_INEXACT
    .endif
    ret

_statusfp endp

    end
