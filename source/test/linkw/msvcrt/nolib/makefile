test.exe:
    asmc64 -q -nolib $*.asm
    linkw op map system dcon_64 file $*
    $@
    pause

