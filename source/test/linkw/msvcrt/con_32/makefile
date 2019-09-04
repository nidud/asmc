test.exe:
    asmc -q -D__PE__ $*.asm
    linkw op map system dcon_32 file $*
    $@
    pause

