; WINSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC Windows 32
;
include stdlib.inc
include winbase.inc
include winuser.inc
include crtl.inc

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND	ENDS

    .code

    dd 495A440Ah
    dd 564A4A50h
    db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

WinStart proc
    mov eax,offset _INIT
    mov edx,offset _IEND
    __initialize(eax, edx)
    mov ebx,GetModuleHandle(0)
    ExitProcess(WinMain(ebx, 0, GetCommandLineA(), SW_SHOWDEFAULT))
WinStart endp

    end WinStart
