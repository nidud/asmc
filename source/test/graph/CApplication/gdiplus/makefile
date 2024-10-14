static = 0

gdiplus.exe:
!if $(static)
    asmc64 -q -ws $*.asm
!else
    asmc64 -peg -ws $*.asm
!endif
    $@
    pause
