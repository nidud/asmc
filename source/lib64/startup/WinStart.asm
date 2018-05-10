; WinStart.asm--
;
; Startup module for LIBC Windows 64
;
include stdlib.inc
include winbase.inc
include winuser.inc
include crtl.inc

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
IStart	label byte
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
IEnd	label byte
_IEND	ENDS

    .code

    dd 495A440Ah
    dd 564A4A50h
    db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

WinStart proc

    lea rcx,IStart
    lea rdx,IEnd
    __initialize(rcx, rdx)
    mov rbx,GetModuleHandle(0)
    ExitProcess(WinMain(rbx, 0, GetCommandLineA(), SW_SHOWDEFAULT))

WinStart endp

    end WinStart
