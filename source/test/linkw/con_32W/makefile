test.exe:
    asmc -q -ws -D_UNICODE $*.asm
    linkw system con_32W file $*
    $@
    pause

