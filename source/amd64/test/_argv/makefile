test.exe:
    asmc -q -D_WIN64 -win64 $*.asm
    linkw system con_64 file $*
    $@ 1 2 3 "4" 5 6 -7"quote" ""8" 9"
    pause
    del $*.obj
    del $@


