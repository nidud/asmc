; STRSAFE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc

    .code

DllMain proc WINAPI hinstDLL:HINSTANCE, fdwReason:DWORD, lpvReserved:ptr

    mov eax,TRUE
    ret

DllMain endp

    end

