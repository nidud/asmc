; MESSAGEBEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

MessageBeep proc WINAPI uType:UINT
    ldr ecx,uType
    xor eax,eax
    .switch ecx
    .case MB_ICONASTERISK
    .case MB_ICONWARNING
    .case MB_ICONQUESTION
    .case MB_ICONERROR
        _write(_confd, "\x7", 1)
    .endsw
    ret
    endp

    end
