; _CONTROLFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_controlfp proc __cdecl newval:UINT, unmask:UINT

    mov eax,unmask
    and eax,not _EM_DENORMAL
    _control87(newval, eax)
    ret

_controlfp endp

    end
