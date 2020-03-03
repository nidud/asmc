static = 0
test.exe:
 !if $(static)
    asmc64 -q $*.asm
    linkw sys con_64 file $*
 !else
    asmc64 -q -pe $*.asm
 !endif
    $@
    pause
    del *.obj
    del *.exe
