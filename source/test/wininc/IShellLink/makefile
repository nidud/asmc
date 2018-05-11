test.exe:
    asmc -q -ws -win64 -Zp8 $*.asm
    linkw system con_64W file $*
    #asmc -q -ws $*.asm
    #linkw system con_32W file $*
    del *.obj
    $@
    pause

