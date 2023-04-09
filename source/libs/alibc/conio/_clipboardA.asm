; _CLIPBOARDA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_clipsetA proc string:LPSTR, len:UINT

    xor eax,eax
    ret

_clipsetA endp


_clipgetA proc

    xor eax,eax
    ret

_clipgetA endp

    end
