test.exe:
    asmc $*.asm
    linkw system con_32 file $*
    $@
    pause
    del $*.obj
    del $@


