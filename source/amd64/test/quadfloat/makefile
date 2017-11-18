test.exe:
    asmc -win64 $*.asm
    linkw system con_64 file $*
    $@
    pause
