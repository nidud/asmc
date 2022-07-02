test.exe:
    asmc64 $*.asm
    linkw system con_64 file $*
    $@
    pause
    del $*.obj
    del $*.exe

