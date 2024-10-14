static = 0

glu.exe:
!if $(static)
    asmc64 -ws $*.asm
!else
    asmc64 -peg -ws $*.asm
!endif
    $@
    pause
