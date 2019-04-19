test.exe:
    asmc64 -Cs $*.asm
    linkw system gui_64 file $*
    $@
    del *.obj
    del *.exe

