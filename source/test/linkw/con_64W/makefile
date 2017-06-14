test.exe:
    asmc -q -win64 -D_WIN64 -ws -D_UNICODE $*.asm
    linkw system con_64W file $*
    $@
    pause

