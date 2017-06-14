
test.exe:
    asmc /win64 /D_WIN64 $*.asm
    linkw system gui_64 file $*
    $@
    del $@
    del $*.obj

