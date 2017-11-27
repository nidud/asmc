msvcrt = 1

dllmake.exe:
!if $(msvcrt)
    asmc -pe -D_WIN64 $*.asm
!else
    asmc -q -win64 $*.asm
    linkw system con_64 file $*
!endif
    $@