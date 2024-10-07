static = 0

thread.exe:
!if $(static)
    asmc64 -ws $*.asm
    linkw system gui_64W file $*.obj
!else
    asmc64 -peg -ws $*.asm
!endif
    $@
    pause
