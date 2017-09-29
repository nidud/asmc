; _CONTROLFP.ASM--
; Copyright (C) 2017 Asmc Developers
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
