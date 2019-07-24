
test.exe:
    asmc -win64 $*.asm
    linkw sys con_64 file $*
    $@
    type $*.ini
    pause
    del $*.obj
    del $*.exe
