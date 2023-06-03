
stat.exe:
    asmc -q -pe $*.asm
    $@
    asmc -q $*.asm
    linkw system con_32 file $*
    $@
    pause
    asmc64 -q -pe $*.asm
    $@
    asmc64 -q $*.asm
    linkw system con_64 file $*
    $@
    pause

