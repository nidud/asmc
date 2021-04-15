
Win64 = 1

FullscreenMagnifierSample.exe:
!if $(Win64)
   asmc64 -ws -pe -gui $*.asm
!else
   asmc -pe -gui -arch:SSE $*.asm
!endif
    $@
