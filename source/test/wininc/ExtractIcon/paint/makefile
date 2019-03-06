dynamic = 1
win64   = 1

test.exe:
!if (dynamic)
 !if (win64)
    asmc64 -pe -gui $*.asm
 !else
    asmc -pe -gui $*.asm
 !endif
!else
 !if (win64)
    asmc64 $*.asm
    linkw sys gui_64 file $*
 !else
    asmc $*.asm
    linkw sys gui_32 file $*
 !endif
!endif
    if exist $@ (
      $@
    )
