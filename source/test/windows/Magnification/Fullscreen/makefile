
Win64 = 0

FullscreenMagnifierSample.exe:
!if $(Win64)
    asmc64 -ws -peg $*.asm
!else
    asmc -ws -peg -arch:SSE $*.asm
!endif
    $@
