
Win64 = 0

MagnifierSample.exe:
!if $(Win64)
   asmc64 -frame -peg $*.asm
!else
   asmc -peg -arch:SSE $*.asm
!endif
    $@
