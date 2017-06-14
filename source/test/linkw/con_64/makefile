test.exe:
    asmc -q -win64 -D_WIN64 $*.asm
    linkw system con_64 file $*
    $@
    pause

