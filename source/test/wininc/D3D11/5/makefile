
pe32 = 1

test.exe:
!if $(pe32)
    asmc -pe -gui $*.asm
!else
    asmc64 $*.asm
    linkw sys gui_64 file $*
!endif
    $@
