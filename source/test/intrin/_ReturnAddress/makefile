test.exe:
    asmc $*.asm
    linkw system con_32 name $*32.exe file $*
    asmc64 $*.asm
    linkw system con_64 file $*
    $@
    pause

