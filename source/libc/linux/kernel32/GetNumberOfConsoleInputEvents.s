; GETNUMBEROFCONSOLEINPUTEVENTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/ioctl.inc
include conio.inc

.code

GetNumberOfConsoleInputEvents proc WINAPI hConsoleInput:HANDLE, lpcNumberOfEvents:LPDWORD
    ldr rcx,hConsoleInput
    ioctl( ecx, FIONREAD, ldr(lpcNumberOfEvents) )
    test eax,eax
    setz al
    movzx eax,al
    ret
    endp

    end
