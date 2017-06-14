msvcrt = 0

_getch.exe:
!if $(msvcrt)
    asmc -pe -D__PE__ -D_WIN64 $*.asm
!else
    asmc -q -win64 -D_WIN64 $*.asm
    linkw system con_64 file $*
    del $*.obj
!endif
    $@
    pause
    del $@


