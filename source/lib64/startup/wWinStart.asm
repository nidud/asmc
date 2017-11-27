; wWinStart.asm--
;
; Startup module for LIBC Windows 64 Unicode
;
include asmcver.inc
include stdlib.inc
include winbase.inc
include winuser.inc
include crtl.inc

_INIT   SEGMENT PARA FLAT PUBLIC 'INIT'
IStart  label byte
_INIT   ENDS
_IEND   SEGMENT PARA FLAT PUBLIC 'INIT'
IEnd    label byte
_IEND   ENDS

    .code

    dd 495A440Ah
    dd 564A4A50h
    db VERSSTR

wWinStart proc

    lea rcx,IStart
    lea rdx,IEnd
    __initialize(rcx, rdx)
    mov rbx,GetModuleHandle(0)
    ExitProcess(wWinMain(rbx, 0, GetCommandLineW(), SW_SHOWDEFAULT))

wWinStart endp

    end wWinStart
