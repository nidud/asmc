
Win64 = 0

MagnifierSample.exe:
!if $(Win64)
   asmc64 -frame -pe -gui $*.asm
!else
   asmc -pe -gui -arch:SSE $*.asm
!endif
    $@
