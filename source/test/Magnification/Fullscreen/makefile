
Win64 = 0

FullscreenMagnifierSample.exe:
!if $(Win64)
    asmc64 -ws -pe -gui $*.asm
!else
    asmc -ws -pe -gui -arch:SSE $*.asm
!endif
    $@
