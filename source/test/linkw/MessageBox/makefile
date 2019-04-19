win64   = 0
static  = 0
unicode = 0

test.exe:
!if $(win64)
 !if $(unicode)
    asmc64 -q -ws $*.asm
    linkw sys gui_64W file $*
 !else
    asmc64 -q $*.asm
    linkw sys gui_64 file $*
 !endif
!else
 !if $(unicode)
    asmc -q -ws $*.asm
    linkw sys gui_32W file $*
 !else
    asmc -q $*.asm
    linkw sys gui_32 file $*
 !endif
!endif
    $@
    pause
    del *.obj
    del *.exe
