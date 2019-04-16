win64   = 0
static  = 0
unicode = 0

test.exe:
!if $(win64)
 !if $(static)
  !if $(unicode)
    asmc64 -q -ws $*.asm
    linkw sys con_64W file $*
  !else
    asmc64 -q $*.asm
    linkw sys con_64 file $*
  !endif
 !else
  !if $(unicode)
    asmc64 -q -pe -ws $*.asm
  !else
    asmc64 -q -pe $*.asm
  !endif
 !endif
!else
 !if $(static)
  !if $(unicode)
    asmc -q -ws $*.asm
    linkw sys con_32W file $*
  !else
    asmc -q $*.asm
    linkw sys con_32 file $*
  !endif
 !else
  !if $(unicode)
    asmc -q -pe -ws $*.asm
  !else
    asmc -q -pe $*.asm
  !endif
 !endif
!endif
    $@
    pause
    del *.obj
    del *.exe
