static = 0

Direct2D.exe:
!if $(static)
    asmc64 -ws $*.asm
    linkw system gui_64W file $*.obj
!else
    asmc64 -pe -ws -gui $*.asm
!endif
    $@
    pause
