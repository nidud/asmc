test.exe:
    asmc -q -ws $*.asm
    linkw system con_32W file $*
    $@
    pause
    del $*.obj
    del $*.exe

