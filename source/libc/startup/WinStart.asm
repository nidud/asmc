; WinStart.asm--
;
; Startup module for LIBC Windows 32
;
include asmcver.inc
include stdlib.inc
include winbase.inc
include winuser.inc
include crtl.inc

_INIT   SEGMENT PARA FLAT PUBLIC 'INIT'
_INIT   ENDS
_IEND   SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND   ENDS

    .code

    dd 495A440Ah
    dd 564A4A50h
    db VERSSTR

WinStart proc
    mov eax,offset _INIT
    mov edx,offset _IEND
    __initialize(eax, edx)
    mov ebx,GetModuleHandle(0)
    ExitProcess(WinMain(ebx, 0, GetCommandLineA(), SW_SHOWDEFAULT))
WinStart endp

    end WinStart
