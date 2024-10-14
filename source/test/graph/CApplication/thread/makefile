static = 0

thread.exe:
!if $(static)
    asmc64 -ws $*.asm
!else
    asmc64 -peg -ws $*.asm
!endif
    $@
    pause
