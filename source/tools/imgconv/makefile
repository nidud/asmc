static = 0

imgconv.exe:
!if $(static)
    asmc64 -ws $*.asm
    linkw system con_64W file $*.obj
!else
    asmc64 -pe -ws $*.asm
!endif
    $@
    pause
