test.exe:
    asmc -q $*.asm
    linkw system con_32 file $*.obj
    $@
    pause
    asmc -q -win64 $*.asm
    linkw system con_64 file $*.obj
    $@
    pause
    del $*.obj
    del $*.exe
