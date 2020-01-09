_aligned_malloc.exe:
    asmc -Fitchar.inc $*.asm
    linkw system con_32 file $*
    $@
    pause
    del $*.obj
    del $*.exe
