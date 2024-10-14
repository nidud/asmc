static = 0

ConsoleEvent.exe:
!if $(static)
    asmc64 -q $*.asm
!else
    asmc64 -pe $*.asm
!endif
    $@
    pause

