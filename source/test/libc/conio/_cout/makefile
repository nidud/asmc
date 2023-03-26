unicode = 1

_cout.exe:
!if $(unicode)
    asmc64 -ws $*.asm
    linkw system con_64W file $*.obj
!else
    asmc64 $*.asm
    linkw system con_64 file $*.obj
!endif
    $@
    pause
