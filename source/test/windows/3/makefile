static = 0

test.exe:
!if $(static)
    asmc $*.asm
    linkw system gui_32 file $*
!else
    asmc -pe -D__PE__ $*.asm
!endif
    $@
    del $*.obj
#   del $*.exe

