test.exe:
    asmc64 -q -ws $*.asm
    linkw system con_64W file $*
    $@
    pause
    del $*.obj
    del $*.exe

