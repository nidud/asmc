win64   = 1
static  = 0
test.exe:
!if $(win64)
 !if $(static)
    asmc64 -q $*.asm
    linkw sys con_64 file $*
 !else
    asmc64 -q -pe $*.asm
 !endif
!else
 !if $(static)
    asmc -q $*.asm
    linkw sys con_32 file $*
 !else
    asmc -q -pe $*.asm
 !endif
!endif
    $@
    pause
    del *.obj
    del *.exe
