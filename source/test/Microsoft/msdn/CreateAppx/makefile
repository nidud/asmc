static = 0

CreateAppx.exe:
!if $(static)
    asmc64 -ws $*.asm
    linkw system con_64W file $*.obj
!else
    asmc64 -pe -ws -Zp8 $*.asm
!endif
    $@
    pause
