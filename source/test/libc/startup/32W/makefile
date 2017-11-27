test.exe:
    asmc /ws $*.asm
    linkw system con_32W file $*
    $@ 1 2 3 "4" 5 6 -7"quote" ""8" 9" "test".asm
    pause
    del $*.obj
    del $@


