static = 0

DirectCompositionEffects.exe:
!if $(static)
    asmc64 -ws -Zp8 $*.asm
    linkw system gui_64W file $*.obj
!else
    asmc64 -ws -pe -gui -Zp8 $*.asm
!endif
    $@

