test.exe:
    asmc -q -win64 $*.asm
    linkw system con_64 file $*.obj
    $@
    pause
    asmc -q -pe -D_WIN64 $*.asm
    $@
    pause
