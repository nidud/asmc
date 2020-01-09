test.exe:
    asmc -win64 -ws $*.asm
    linkw sys con_64W file $*
    $@
    pause
    del $*.obj
    del $*.exe


