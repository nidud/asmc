static = 0

test.exe:
!if $(static)
    asmc64 $*.asm
    linkw system con_64 file $*.obj
!else
    asmc -ws -pe $*.asm
!endif
    $@
