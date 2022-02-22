test.exe:
    asmc64 $*.asm
    linkw system con_64 file $*
    $@
    pause
    asmc $*.asm
    linkw system con_32 file $*
    $@
    pause

