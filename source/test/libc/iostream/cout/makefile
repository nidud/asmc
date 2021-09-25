
cout.exe:
    asmc64 $*.asm
    asmc64 stdio.asm
    linkw system con_64 file $*
    linkw system con_64 file stdio
    del *.obj
    echo cout.exe:
    $@
    echo stdio.exe:
    stdio
    dir *.exe
    pause
