test.exe:
    asmc -q $*.asm
    linkw op map system con_32 file $*
    $@
    pause
    del $*.obj
    del $*.exe

