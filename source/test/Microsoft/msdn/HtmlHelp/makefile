static = 0

test.exe:
!if $(static)
    asmc64 $*.asm
!else
    asmc -ws -pe $*.asm
!endif
    $@
