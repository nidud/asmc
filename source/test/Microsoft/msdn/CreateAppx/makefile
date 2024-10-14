static = 0

CreateAppx.exe:
!if $(static)
    asmc64 -q -ws $*.asm
!else
    asmc64 -pe -ws -Zp8 $*.asm
!endif
    $@
    pause
