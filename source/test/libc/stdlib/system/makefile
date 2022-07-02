
test.exe:
    asmc -q $*.asm
    linkw system con_32 file $*
    $@
    asmc64 -q -Zp8 -Cs $*.asm
    linkw system con_64 file $*
    $@
    asmc -q -ws -Cs $*.asm
    linkw system con_32W file $*
    $@
    asmc64 -q -Zp8 -ws -Cs $*.asm
    linkw system con_64W file $*
    $@
    pause
    del $*.obj
    del $@
