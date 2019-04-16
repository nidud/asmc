win64   = 0
static  = 0
unicode = 1

test.exe:
!if $(win64)
 !if $(static)
  !if $(unicode)
    asmc64 -q -ws $*.asm
    linkw sys con_64W file $*
  !else
  !endif
 !else
  !if $(unicode)
    asmc64 -q -pe -ws $*.asm
  !else
  !endif
 !endif
!else
 !if $(static)
  !if $(unicode)
    asmc -q -ws $*.asm
    linkw sys con_32W file $*
  !else
  !endif
 !else
  !if $(unicode)
    asmc -q -pe -ws $*.asm
  !else
  !endif
 !endif
!endif
    $@
    pause
    del *.obj
    del *.exe
