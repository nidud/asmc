dynamic = 1
win64   = 1

test.exe:
!if (dynamic)
 !if (win64)
    asmc64 -pe -ws -gui $*.asm
 !else
    asmc -pe -ws -gui $*.asm
 !endif
!else
!if (win64)
    asmc64 -ws $*.asm
    linkw sys gui_64W file $*
!else
    asmc -ws $*.asm
    linkw sys gui_32 file $*
!endif
!endif
    if exist $@ (
      $@
    )
