msvc = 0

lcount.exe:
!if $(msvc)
    asmc -pe -D__PE__ -D_WIN64 $*.asm
!else
    asmc -q -win64 $*.asm
    linkw system con_64 file $*
    del *.obj
!endif
    $@ -r ..\*.asm
    pause

