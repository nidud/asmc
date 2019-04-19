test.exe:
    asmc -q $*.asm
    linkw system con_32 file $*
    $@
    pause
    del $*.obj
    del $*.exe

