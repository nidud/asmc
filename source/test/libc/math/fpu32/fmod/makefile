test.exe:
    asmc -q $*.asm
    linkw system con_32 file $*.obj
    $@
    pause
    asmc -q -pe -D__PE__ $*.asm
    $@
    pause
