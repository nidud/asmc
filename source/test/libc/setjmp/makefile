setjmp.exe:
    asmc -q $*.asm
    linkw system con_32 file $*
    $@
    pause
    asmc64 -q $*.asm
    linkw system con_64 file $*
    $@
    pause
    asmc -q -ws $*.asm
    linkw system con_32W file $*
    $@
    pause
    asmc64 -q -ws $*.asm
    linkw system con_64W file $*
    $@
    pause
    del $*.obj
    del $*.exe

