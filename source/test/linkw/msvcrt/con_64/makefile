test.exe:
    asmc64 -q -D__PE__ $*.asm
    linkw op map system dcon_64 file $*
    $@
    pause

