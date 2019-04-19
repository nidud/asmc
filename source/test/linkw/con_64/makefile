test.exe:
    asmc64 -q $*.asm
    linkw system con_64 file $*
    $@
    pause
    del $*.obj
    del $*.exe

